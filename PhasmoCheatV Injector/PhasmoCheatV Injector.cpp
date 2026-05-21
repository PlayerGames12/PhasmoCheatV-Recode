#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <random>
#include <versionhelpers.h>
#pragma comment(lib, "version.lib")

constexpr const char* kProcessName = "Phasmophobia.exe";
constexpr const char* kDllName = "PhasmoCheatV Recode.dll";
constexpr const char* kRequiredVersion = "14.50.35719.0";

bool IsVersionAtLeast(const char* current, const char* required)
{
    int currentMajor, currentMinor, currentBuild, currentRevision;
    int requiredMajor, requiredMinor, requiredBuild, requiredRevision;

    sscanf_s(current, "%d.%d.%d.%d", &currentMajor, &currentMinor, &currentBuild, &currentRevision);
    sscanf_s(required, "%d.%d.%d.%d", &requiredMajor, &requiredMinor, &requiredBuild, &requiredRevision);

    if (currentMajor > requiredMajor) return true;
    if (currentMajor < requiredMajor) return false;

    if (currentMinor > requiredMinor) return true;
    if (currentMinor < requiredMinor) return false;

    if (currentBuild > requiredBuild) return true;
    if (currentBuild < requiredBuild) return false;

    return currentRevision >= requiredRevision;
}

bool IsMsvcVersionCorrect()
{
    char systemDir[MAX_PATH];
    GetSystemDirectoryA(systemDir, MAX_PATH);
    std::string msvcPath = std::string(systemDir) + "\\msvcp140.dll";

    DWORD versionHandle = 0;
    DWORD versionSize = GetFileVersionInfoSizeA(msvcPath.c_str(), &versionHandle);

    if (versionSize == 0) return false;

    std::vector<char> versionData(versionSize);
    if (!GetFileVersionInfoA(msvcPath.c_str(), 0, versionSize, versionData.data())) return false;

    VS_FIXEDFILEINFO* fileInfo = nullptr;
    UINT fileInfoSize = 0;

    if (!VerQueryValueA(versionData.data(), "\\", (LPVOID*)&fileInfo, &fileInfoSize)) return false;

    WORD major = HIWORD(fileInfo->dwFileVersionMS);
    WORD minor = LOWORD(fileInfo->dwFileVersionMS);
    WORD build = HIWORD(fileInfo->dwFileVersionLS);
    WORD revision = LOWORD(fileInfo->dwFileVersionLS);

    char currentVersion[32];
    sprintf_s(currentVersion, "%d.%d.%d.%d", major, minor, build, revision);

    return IsVersionAtLeast(currentVersion, kRequiredVersion);
}

bool GetUserChoice()
{
    std::string input;
    std::cout << "\nVC Redist version is below required minimum! Minimum required: " << kRequiredVersion << std::endl;
    std::cout << "Skip check? (1/y/yes or 0/n/no): ";
    std::getline(std::cin, input);

    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    return (input == "1" || input == "y" || input == "yes");
}

DWORD GetProcessId(const char* name)
{
    PROCESSENTRY32 pe{ sizeof(pe) };
    HANDLE s = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (s == INVALID_HANDLE_VALUE) return 0;
    if (!Process32First(s, &pe)) return 0;
    do
    {
        char b[MAX_PATH];
        wcstombs_s(nullptr, b, pe.szExeFile, MAX_PATH);
        if (!lstrcmpA(b, name)) return pe.th32ProcessID;
    } while (Process32Next(s, &pe));
    return 0;
}

bool SelectDll(char* p)
{
    OPENFILENAMEA o{};
    o.lStructSize = sizeof(o);
    o.lpstrFilter = "DLL (.dll)\0.dll\0";
    o.lpstrFile = p;
    o.nMaxFile = MAX_PATH;
    o.Flags = OFN_FILEMUSTEXIST;
    return GetOpenFileNameA(&o);
}

std::string GenerateRandomName()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 61);

    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string result = "ph_";

    for (int i = 0; i < 12; ++i) {
        result += charset[dis(gen)];
    }

    result += ".vt";

    return result;
}

bool CopyToTemp(const char* src, char* out)
{
    char tp[MAX_PATH];
    GetTempPathA(MAX_PATH, tp);

    std::string randomName = GenerateRandomName();
    std::string fullPath = std::string(tp) + randomName;

    strcpy_s(out, MAX_PATH, fullPath.c_str());
    return CopyFileA(src, out, FALSE);
}

int main()
{
    SetConsoleTitleA("PhasmoCheatV Injector");

    std::cout << "Checking VC Redist version..." << std::endl;

    if (!IsMsvcVersionCorrect())
    {
        if (!GetUserChoice())
        {
            std::cout << "Injection cancelled by user." << std::endl;
            std::cin.get();
            return 0;
        }
        std::cout << "Check skipped, continuing..." << std::endl;
    }
    else
    {
        std::cout << "VC Redist version OK!" << std::endl;
    }

    char dll[MAX_PATH]{};
    GetFullPathNameA(kDllName, MAX_PATH, dll, nullptr);
    if (GetFileAttributesA(dll) == INVALID_FILE_ATTRIBUTES)
        if (!SelectDll(dll)) return 0;

    DWORD pid = GetProcessId(kProcessName);
    if (!pid)
    {
        std::cout << "Process not found!" << std::endl;
        return 0;
    }

    HANDLE p = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!p)
    {
        std::cout << "Failed to open process!" << std::endl;
        return 0;
    }

    std::cout << "PID: " << pid << std::endl;

    char tmp[MAX_PATH]{};
    if (!CopyToTemp(dll, tmp))
    {
        std::cout << "Failed to copy DLL to temp!" << std::endl;
        return 0;
    }

    std::cout << "DLL: " << tmp << std::endl;

    void* r = VirtualAllocEx(p, nullptr, lstrlenA(tmp) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!r)
    {
        std::cout << "Failed to allocate memory!" << std::endl;
        return 0;
    }

    WriteProcessMemory(p, r, tmp, lstrlenA(tmp) + 1, nullptr);

    auto ll = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    if (!ll)
    {
        std::cout << "Failed to get LoadLibraryA!" << std::endl;
        return 0;
    }

    HANDLE t = CreateRemoteThread(p, nullptr, 0, (LPTHREAD_START_ROUTINE)ll, r, 0, nullptr);
    if (!t)
    {
        std::cout << "Failed to create remote thread!" << std::endl;
        return 0;
    }

    WaitForSingleObject(t, INFINITE);

    std::cout << "Inject completed successfully!" << std::endl;
    std::cout << "Press Enter to exit...";
    std::cin.get();

    CloseHandle(p);
    CloseHandle(t);

    return 0;
}
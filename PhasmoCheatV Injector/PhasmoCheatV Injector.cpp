#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <vector>
#include <string>
#include <regex>
#include <iostream>

constexpr const char* kProcessName = "Phasmophobia.exe";
constexpr const char* kDllName = "PhasmoCheatV Recode.dll";

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
    o.lpstrFilter = "DLL (*.dll)\0*.dll\0";
    o.lpstrFile = p;
    o.nMaxFile = MAX_PATH;
    o.Flags = OFN_FILEMUSTEXIST;
    return GetOpenFileNameA(&o);
}

std::string Cut(const char* s)
{
    std::regex r(R"((\d\.\d{2}\.\d\.\d))");
    std::cmatch m;
    if (std::regex_search(s, m, r)) return m.str(1);
    return {};
}

void PrintVersion(HANDLE p)
{
    HMODULE m;
    MODULEINFO i{};
    DWORD cb;
    EnumProcessModules(p, &m, sizeof(m), &cb);
    GetModuleInformation(p, m, &i, sizeof(i));
    std::vector<uint8_t> b(i.SizeOfImage);
    ReadProcessMemory(p, i.lpBaseOfDll, b.data(), b.size(), nullptr);
    for (size_t x = 0; x + 9 < b.size(); x++)
        if (b[x] == 0x33 && b[x + 1] == 0x30 && b[x + 2] == 0x2E && b[x + 3] == 0x31 && b[x + 5] == 0x2E && b[x + 7] == 0x2E)
        {
            auto v = Cut((char*)(b.data() + x));
            if (!v.empty())
            {
                std::cout << "Version: " << v << std::endl;
                return;
            }
        }
}

bool CopyToTemp(const char* src, char* out)
{
    char tp[MAX_PATH];
    GetTempPathA(MAX_PATH, tp);
    char tf[MAX_PATH];
    GetTempFileNameA(tp, "ph", 0, tf);
    lstrcpyA(out, tf);
    lstrcatA(out, ".dll");
    return CopyFileA(src, out, FALSE);
}

int main()
{
    char dll[MAX_PATH]{};
    GetFullPathNameA(kDllName, MAX_PATH, dll, nullptr);
    if (GetFileAttributesA(dll) == INVALID_FILE_ATTRIBUTES)
        if (!SelectDll(dll)) return 0;

    DWORD pid = GetProcessId(kProcessName);
    if (!pid) return 0;

    HANDLE p = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!p) return 0;

    std::cout << "PID: " << pid << std::endl;
    PrintVersion(p);

    char tmp[MAX_PATH]{};
    if (!CopyToTemp(dll, tmp)) return 0;

    std::cout << "DLL: " << tmp << std::endl;

    void* r = VirtualAllocEx(p, nullptr, lstrlenA(tmp) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!r) return 0;

    WriteProcessMemory(p, r, tmp, lstrlenA(tmp) + 1, nullptr);

    auto ll = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    if (!ll) return 0;

    HANDLE t = CreateRemoteThread(p, nullptr, 0, (LPTHREAD_START_ROUTINE)ll, r, 0, nullptr);
    if (!t) return 0;

    WaitForSingleObject(t, INFINITE);

    std::cout << "Inject completed" << std::endl;
    std::cin.get();
    return 0;
}

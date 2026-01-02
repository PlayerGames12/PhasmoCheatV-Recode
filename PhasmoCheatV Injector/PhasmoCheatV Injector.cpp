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

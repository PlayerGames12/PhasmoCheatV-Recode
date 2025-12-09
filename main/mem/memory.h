#include <windows.h>
#include <vector>
#include <string>
#include <cstdint>

namespace Memory {

    void* FindPattern(const char* moduleName, const char* patternStr);

    template <typename T>
    T Read(void* address) {
        if (!address) return T();
        return *(T*)address;
    }

    template <typename T>
    void Write(void* address, T value) {
        if (!address) return;
        DWORD oldProtect;
        VirtualProtect(address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);
        *(T*)address = value;
        VirtualProtect(address, sizeof(T), oldProtect, &oldProtect);
    }

}
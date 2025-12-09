#include "memory.h"
#include <sstream>
#include <iomanip>

namespace Memory {

    void* FindPattern(const char* moduleName, const char* patternStr) {
        HMODULE module = GetModuleHandleA(moduleName);
        if (!module) return nullptr;

        // Get DOS and NT headers
        PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
        PIMAGE_NT_HEADERS ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uintptr_t>(module) + dosHeader->e_lfanew);

        // Find .text section
        PIMAGE_SECTION_HEADER sectionHeader = IMAGE_FIRST_SECTION(ntHeaders);
        PIMAGE_SECTION_HEADER textSection = nullptr;
        for (int i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i) {
            if (std::string(reinterpret_cast<char*>(sectionHeader->Name)) == ".text") {
                textSection = sectionHeader;
                break;
            }
            ++sectionHeader;
        }
        if (!textSection) return nullptr;

        uintptr_t sectionStart = reinterpret_cast<uintptr_t>(module) + textSection->VirtualAddress;
        size_t sectionSize = textSection->Misc.VirtualSize;

        // Parse pattern into bytes and mask
        std::vector<uint8_t> patternBytes;
        std::vector<bool> mask;
        std::istringstream iss(patternStr);
        std::string token;
        while (iss >> token) {
            if (token == "??") {
                patternBytes.push_back(0);  // Dummy byte
                mask.push_back(false);
            }
            else {
                uint8_t byte = static_cast<uint8_t>(std::stoi(token, nullptr, 16));
                patternBytes.push_back(byte);
                mask.push_back(true);
            }
        }

        if (patternBytes.empty()) return nullptr;

        // Scan for pattern
        for (size_t i = 0; i < sectionSize - patternBytes.size(); ++i) {
            bool found = true;
            for (size_t j = 0; j < patternBytes.size(); ++j) {
                if (mask[j] && reinterpret_cast<uint8_t*>(sectionStart + i + j)[0] != patternBytes[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return reinterpret_cast<void*>(sectionStart + i);
            }
        }

        return nullptr;
    }

}
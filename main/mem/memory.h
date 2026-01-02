#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <mutex>
#include <Windows.h>
#include <Psapi.h>

namespace Memory
{
	struct Pattern
	{
		std::vector<uint8_t> Bytes;
		std::vector<bool> Mask;
	};

	struct ModuleSection
	{
		uintptr_t Base;
		size_t Size;
	};

	// Convert IDA-style pattern (like "48 8B 05 ? ? ? ?") to internal pattern format
	Pattern ParsePattern(const std::string& pattern);

	// Get specific module section (.text, .data, etc)
	ModuleSection GetModuleSection(HMODULE module, const char* sectionName);

	// Find pattern in memory range
	uintptr_t FindPattern(uintptr_t start, size_t size, const Pattern& pattern);

	// Convenience overload that takes string pattern directly
	uintptr_t FindPattern(uintptr_t start, size_t size, const std::string& pattern);

	// Find pattern in specific module section
	uintptr_t FindPatternInSection(HMODULE module, const char* sectionName, const std::string& pattern);

	// Find pattern in all sections of a module
	uintptr_t FindPatternInAllSections(HMODULE module, const std::string& pattern);

	uintptr_t FindPatternInSection_more(HMODULE module, const char* sectionName, const std::string& pattern, uintptr_t startOffset);

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
} // Thanks Evelien
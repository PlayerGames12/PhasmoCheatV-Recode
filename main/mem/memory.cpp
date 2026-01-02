#include "../Includes.h"
#include "memory.h"
#include <sstream>
#include <cctype>
#include <Windows.h>
#include <immintrin.h>

namespace Memory
{
	ModuleSection GetModuleSection(HMODULE module, const char* sectionName)
	{
		ModuleSection result{ 0, 0 };
		if (!module || !sectionName)
			return result;

		const auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
		if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
			return result;

		const auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uintptr_t>(module) + dosHeader->e_lfanew);
		if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
			return result;

		const auto sectionHeader = IMAGE_FIRST_SECTION(ntHeaders);
		const auto numSections = ntHeaders->FileHeader.NumberOfSections;

		for (WORD i = 0; i < numSections; i++)
		{
			const auto section = &sectionHeader[i];
			char sectionNameStr[9] = { 0 };
			memcpy(sectionNameStr, section->Name, 8);

			if (_stricmp(sectionNameStr, sectionName) == 0)
			{
				result.Base = reinterpret_cast<uintptr_t>(module) + section->VirtualAddress;
				result.Size = section->Misc.VirtualSize;
				LOG_DEBUG("Found section {} at {} with size {}",
					sectionName, std::hex, result.Base, std::dec, result.Size);
				break;
			}
		}

		return result;
	}

	Pattern ParsePattern(const std::string& pattern)
	{
		Pattern result;
		result.Bytes.reserve(32);
		result.Mask.reserve(32);

		if (pattern.empty())
		{
			LOG_DEBUG("Empty pattern provided to ParsePattern");
			return result;
		}

		try
		{
			const char* ptr = pattern.c_str();
			const char* end = ptr + pattern.length();

			while (ptr < end)
			{
				while (ptr < end && std::isspace(*ptr)) ptr++;
				if (ptr >= end) break;

				if (*ptr == '?')
				{
					result.Bytes.push_back(0);
					result.Mask.push_back(false);
					ptr += (ptr + 1 < end && ptr[1] == '?') ? 2 : 1;
					continue;
				}

				if (ptr + 1 >= end) break;

				auto hexToInt = [](const char c) -> int
					{
						if (c >= '0' && c <= '9') return c - '0';
						if (c >= 'a' && c <= 'f') return c - 'a' + 10;
						if (c >= 'A' && c <= 'F') return c - 'A' + 10;
						return -1;
					};

				const int high = hexToInt(ptr[0]);
				const int low = hexToInt(ptr[1]);

				if (high == -1 || low == -1)
				{
					LOG_DEBUG("Invalid hex byte in pattern");
					result.Bytes.clear();
					result.Mask.clear();
					return result;
				}

				result.Bytes.push_back(static_cast<uint8_t>((high << 4) | low));
				result.Mask.push_back(true);
				ptr += 2;
			}
		}
		catch (const std::exception& e)
		{
			LOG_DEBUG("Exception in ParsePattern: {}", e.what());
			result.Bytes.clear();
			result.Mask.clear();
		}

		return result;
	}

	uintptr_t FindPattern(const uintptr_t start, const size_t size, const Pattern& pattern)
	{
		if (pattern.Bytes.empty() || size < pattern.Bytes.size() || !start)
			return 0;

		const auto data = reinterpret_cast<const uint8_t*>(start);
		const size_t patternSize = pattern.Bytes.size();
		const size_t scanSize = size - patternSize + 1;

		if (patternSize < 4)
		{
			for (size_t i = 0; i < scanSize; ++i)
			{
				bool found = true;
				for (size_t j = 0; j < patternSize; ++j)
				{
					if (pattern.Mask[j] && data[i + j] != pattern.Bytes[j])
					{
						found = false;
						break;
					}
				}
				if (found)
					return start + i;
			}
			return 0;
		}

		uint32_t firstBytes = 0;
		uint32_t firstMask = 0;
		for (size_t i = 0; i < 4 && i < patternSize; ++i)
		{
			if (pattern.Mask[i])
			{
				firstBytes |= (pattern.Bytes[i] << (i * 8));
				firstMask |= (0xFF << (i * 8));
			}
		}

		for (size_t i = 0; i < scanSize; ++i) {  // Changed i += 4 to ++i
			const uint32_t value = *reinterpret_cast<const uint32_t*>(data + i);
			if ((value & firstMask) != firstBytes) continue;
			bool found = true;
			for (size_t j = 0; j < patternSize; ++j) {
				if (pattern.Mask[j] && data[i + j] != pattern.Bytes[j]) {
					found = false;
					break;
				}
			}
			if (found) return start + i;
		}

		return 0;
	}

	uintptr_t FindPatternInSection(const HMODULE module, const char* sectionName, const std::string& pattern)
	{
		if (!module || !sectionName)
		{
			LOG_ERROR("Invalid module or section name");
			return 0;
		}

		const auto section = GetModuleSection(module, sectionName);
		if (!section.Base || !section.Size)
		{
			LOG_ERROR("Failed to get section {} in module", sectionName);
			return 0;
		}

		MEMORY_BASIC_INFORMATION mbi;
		if (!VirtualQuery(reinterpret_cast<LPCVOID>(section.Base), &mbi, sizeof(mbi)) ||
			!(mbi.Protect & (PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_READWRITE | PAGE_READONLY)))
		{
			LOG_ERROR("Section {} is not readable (protection: {})", sectionName, std::hex, mbi.Protect);
			return 0;
		}

		const auto result = FindPattern(section.Base, section.Size, pattern);
		if (result)
		{
			LOG_DEBUG("Found pattern in section {} at offset {:x}", sectionName, result - section.Base);
		}
		return result;
	}

	uintptr_t FindPattern(const uintptr_t start, const size_t size, const std::string& pattern)
	{
		const auto parsedPattern = ParsePattern(pattern);
		return parsedPattern.Bytes.empty() ? 0 : FindPattern(start, size, parsedPattern);
	}

	uintptr_t FindPatternInAllSections(HMODULE module, const std::string& pattern)
	{
		if (!module)
		{
			LOG_ERROR("Invalid module");
			return 0;
		}

		const auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
		if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
			return 0;

		const auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uintptr_t>(module) + dosHeader->e_lfanew);
		if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
			return 0;

		const auto sectionHeader = IMAGE_FIRST_SECTION(ntHeaders);
		const auto numSections = ntHeaders->FileHeader.NumberOfSections;

		const auto parsedPattern = ParsePattern(pattern);
		if (parsedPattern.Bytes.empty())
			return 0;

		for (WORD i = 0; i < numSections; i++)
		{
			const auto section = &sectionHeader[i];
			char sectionName[9] = { 0 };
			memcpy(sectionName, section->Name, 8);

			const auto sectionBase = reinterpret_cast<uintptr_t>(module) + section->VirtualAddress;
			const auto sectionSize = section->Misc.VirtualSize;

			LOG_INFO("Scanning section {} at base {:x} with size {}", sectionName, sectionBase, sectionSize);

			MEMORY_BASIC_INFORMATION mbi;
			if (VirtualQuery(reinterpret_cast<LPCVOID>(sectionBase), &mbi, sizeof(mbi)))
			{
				if (mbi.Protect & (PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_READWRITE | PAGE_READONLY))
				{
					const auto result = FindPattern(sectionBase, sectionSize, parsedPattern);
					if (result)
					{
						LOG_DEBUG("Found pattern in section {} at offset {:x}", sectionName, result - sectionBase);
						return result;
					}
				}
				else
				{
					LOG_DEBUG("Section {} is not readable (protection: {:x})", sectionName, mbi.Protect);
				}
			}
		}
		return 0;
	}

	uintptr_t FindPatternInSection_more(HMODULE module, const char* sectionName, const std::string& pattern, uintptr_t startOffset)
	{
		if (!module || !sectionName)
			return 0;

		const auto section = GetModuleSection(module, sectionName);
		if (!section.Base || !section.Size)
			return 0;

		if (startOffset < section.Base || startOffset >= section.Base + section.Size)
			startOffset = section.Base;

		size_t size = (section.Base + section.Size) - startOffset;

		MEMORY_BASIC_INFORMATION mbi;
		if (!VirtualQuery(reinterpret_cast<LPCVOID>(startOffset), &mbi, sizeof(mbi)) ||
			!(mbi.Protect & (PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_READWRITE | PAGE_READONLY)))
			return 0;

		return FindPattern(startOffset, size, pattern);
	}
}
#pragma once
#include "../Includes.h"

using Id3DPresent = HRESULT(__stdcall*)(IDXGISwapChain* this_, UINT sync_, UINT flags_);

namespace PhasmoCheatV
{
	class Hooking
	{
		friend Hooks;

	public:
		explicit Hooking();
		~Hooking();

		void AddHook(const std::string& functionName, PVOID* originalFunction, PVOID hookFunction);
		void ApplyHooks() const;
		void RemoveHooks() const;
		Id3DPresent OriginalPresent{};
		WNDPROC OriginalWndproc{};

	private:
		std::vector<std::tuple<std::string, PVOID*, PVOID>> hooks_;
	};

	inline Hooking* hooking{};
}

inline std::string GenerateRandomString(size_t length = 16) {
    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";

    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> dist(0, sizeof(alphanum) - 2);

    std::string result;
    result.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        result += alphanum[dist(rng)];
    }
    return result;
}

#define AHK(orig, hook) PhasmoCheatV::hooking->AddHook(#orig, reinterpret_cast<PVOID*>(&(orig)), reinterpret_cast<PVOID>(hook))
#define AHKA(name) AHK(SDK::name, Hooks::hk##name)
#define PHK(NAME, HOOK) \
    PhasmoCheatV::hooking->AddHook( \
        #NAME, \
        reinterpret_cast<PVOID*>(&SDK::GetOriginal_##NAME()), \
        reinterpret_cast<PVOID>(HOOK) \
    )
#define AHKO(orig, hook) \
    [&]() { \
        static std::string obfuscatedName = GenerateRandomString(16); \
        PhasmoCheatV::hooking->AddHook( \
            obfuscatedName, \
            reinterpret_cast<PVOID*>(&(orig)), \
            reinterpret_cast<PVOID>(hook) \
        ); \
    }()
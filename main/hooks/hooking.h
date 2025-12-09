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

#define AHK(orig, hook) PhasmoCheatV::hooking->AddHook(#orig, reinterpret_cast<PVOID*>(&(orig)), reinterpret_cast<PVOID>(hook))
#define AHKA(name) AHK(SDK::name, Hooks::hk##name)

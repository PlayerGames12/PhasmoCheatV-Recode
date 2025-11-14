#pragma once
#include "../Includes.h"

namespace PhasmoCheatV
{
	struct Hooks
	{
		// Hook menu
		static HRESULT HkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
		static LRESULT HkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		// Other hooks
		static void hkGhostAI_Start(SDK::GhostAI* ghostAI, SDK::MethodInfo* methodInfo);
		static void hkExitLevel_Exit(SDK::ExitLevel* exitLevel, void* photon, SDK::MethodInfo* methodInfo);
	};
}
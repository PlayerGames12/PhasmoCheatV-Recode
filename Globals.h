#pragma once
#include <atomic>
#include <Windows.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

namespace PhasmoCheatV::Globals
{
	// DEBUG
	inline bool IsDebugging = false; 
	inline bool IsCalledLogs = false;
	inline bool IsUpdateCalledLogs = false;
	inline bool RedirectUnityLogs = false; // Warning! A lot of spam
	inline std::chrono::steady_clock::time_point CheatInjectedTime = std::chrono::steady_clock::now();
	inline bool ForTestsFlag = false;

	// MAIN
	inline HMODULE globalModule{};
	inline std::atomic<bool> CheatWork{ false };
	inline bool isHunting = false;
	inline int MenuToggleKey = VK_RETURN;

	// IMGUI
	inline float dpiScale = GetDpiForSystem() / 96.0f;
	inline constexpr ImGuiWindowFlags WINDOW_FLAGS_GLOBALS =
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoResize;
}

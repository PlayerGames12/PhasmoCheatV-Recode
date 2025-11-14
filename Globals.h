#pragma once
#include <atomic>
#include <Windows.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

namespace PhasmoCheatV::Globals
{
	inline HMODULE globalModule{};
	inline std::atomic<bool> CheatWork{ false };
	inline bool IsDebugging = true;
	inline bool IsCalledLogs = true;
	inline float dpiScale = GetDpiForSystem() / 96.0f;

	inline int MenuToggleKey = VK_DELETE;   

	inline constexpr ImGuiWindowFlags WINDOW_FLAGS_GLOBALS =
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoResize;
}
 
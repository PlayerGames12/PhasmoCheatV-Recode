#include "../Includes.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

using namespace PhasmoCheatV;

LRESULT __stdcall Hooks::HkWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    POINT mPos;
    GetCursorPos(&mPos);
    ScreenToClient(Renderer::Window, &mPos);

    ImGui::GetIO().MousePos.x = mPos.x;
    ImGui::GetIO().MousePos.y = mPos.y;

    if (uMsg == WM_KEYUP && wParam == MenuToggleKey)
    {
        menu.Toggle();
    }

    if (uMsg == WM_KEYUP && wParam == VK_END)
    {
        NOTIFY_WARNING_QUICK("You have pressed the emergency unload button. Goodbye.");
        Globals::CheatWork = false;
	}

    if (uMsg == WM_KEYUP && wParam == VK_HOME)
    {
        Globals::MenuToggleKey = VK_RETURN;
        NOTIFY_INFO_QUICK("The menu opening button has been reset.");
    }

	if (uMsg == WM_KEYUP && wParam == VK_DELETE)
    {
        Globals::IsDebugging = !Globals::IsDebugging;
        Globals::IsCalledLogs = !Globals::IsCalledLogs;
		NOTIFY_INFO_QUICK(std::format("Debug Mode {}", Globals::IsDebugging ? "enabled" : "disabled"));
    }

    if (menu.Open)
    {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
        return true;
    }

    return CallWindowProc(hooking->OriginalWndproc, hWnd, uMsg, wParam, lParam);
}
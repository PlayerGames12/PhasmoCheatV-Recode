#include <Windows.h>
#include "Includes.h"
#include "globals.h"
#include "memory.h"

using namespace PhasmoCheatV;

// Global module handle
static std::unique_ptr<Logger> loggerInstance;
static std::unique_ptr<Renderer> rendererInstance;
static std::unique_ptr<Hooking> hookingInstance;
static std::unique_ptr<FeatureHandler> featureInstance;

// Main cheat thread
extern "C" __declspec(dllexport) DWORD WINAPI PhasmoCheatVThread()
{
    try {
        loggerInstance = std::make_unique<Logger>(Logger::Level::Call);
    }
    catch (...) {
        return 0;
    }
	// Initialize SDK
    if (!SDK::Initialize()) {
        LOG_ERROR("Failed to initialize SDK");
        return 0;
    }

    try {
        rendererInstance = std::make_unique<Renderer>();
        hookingInstance = std::make_unique<Hooking>();
        featureInstance = std::make_unique<FeatureHandler>();

        hookingInstance->OriginalPresent = rendererInstance->GetPresent();

		// Set up hooks
        AHK(hookingInstance->OriginalPresent, Hooks::HkPresent);
        AHK(SDK::GhostAI_Start, Hooks::hkGhostAI_Start);
        AHK(SDK::ExitLevel_Exit, Hooks::hkExitLevel_Exit);

        hookingInstance->ApplyHooks();

        LOG_INFO("Cheat injected successfully");

        while (CheatWork) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        LOG_INFO("Starting cleanup...");

        if (rendererInstance && ImGui::SaveIniSettingsToDisk) {
            ImGui::SaveIniSettingsToDisk((Utils::GetPhasmoCheatVDirectory() + "\\menu.ini").c_str());
        }

        hookingInstance->RemoveHooks();
        hookingInstance.reset();
        rendererInstance.reset();
        featureInstance.reset();

        LOG_INFO("Cleanup completed");

    }
    catch (const std::exception& e) {
        LOG_ERROR(std::string("Exception in main thread: ") + e.what());
    }

    loggerInstance.reset();

    FreeConsole();
    CloseHandle(globalModule);
    FreeLibraryAndExitThread(globalModule, NULL);
    return 0;
}

// DLL entry point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CheatWork = true;
        DisableThreadLibraryCalls(hModule);
        globalModule = hModule;

        HANDLE hThread = CreateThread(nullptr, 0,
            reinterpret_cast<LPTHREAD_START_ROUTINE>(PhasmoCheatVThread),
            nullptr, 0, nullptr);

        if (hThread)
            CloseHandle(hThread);

        break;
    }

    case DLL_PROCESS_DETACH:
        CheatWork = false;
        Sleep(100);
        break;
    }

    return TRUE;
}

#include <Windows.h>
#include "Includes.h"
#include "globals.h"
#include "memory.h"
#include "main/config/config.h"

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

        Config::LoadConfig();

        if (IsDebugging)
            LOG_WARN("The build is built with the IsDebugging flag in the true state, followed by the appearance of the console, as well as the execution of Test functions!");

        // Set up hooks
        AHK(hookingInstance->OriginalPresent, Hooks::HkPresent); // using ADD_HOOK
        AHKA(LevelController_Start); // using ADD_HOOK_AUTO
        AHKA(ExitLevel_Exit);
        AHKA(MapController_Start);
        AHKA(GhostAI_Start);
        AHKA(GameController_Exit);
        AHKA(PauseMenuController_Leave);
        AHKA(GhostAI_Hunting);
        AHKA(GhostAI_Update);
        AHKA(EvidenceController_Start);
        AHKA(EMFData_Start);
        AHKA(Player_StartKillingPlayer);
        AHKA(Player_StartKillingPlayerNetworked);
        AHKA(GhostInfo_SyncValuesNetworked);
        AHKA(GhostInfo_SyncEvidence);
        AHKA(PhotonObjectInteract_Start);
        AHKA(FirstPersonController_Update);
        AHKA(TarotCard_SetCard);
        AHKA(PlayerStamina_Update);
        AHKA(ExitLevel_ThereAreAlivePlayersOutsideTheTruck);
        AHKA(ServerManager_KickPlayerNetworked);
        AHKA(ObjectiveManager_Update);
        AHKA(LevelValues_GetInvestigationBonusReward);
        AHKA(LevelValues_IsPerfectGame);
        AHKA(MediaValues_GetRewardAmount);
        AHKA(Key_Start);
        AHKA(SaltShaker_Update);
        AHKA(SaltSpot_SyncSalt);
        AHKA(LevelSelectionManager_Start);
		AHKA(Application_CallLogCallback);

        hookingInstance->ApplyHooks();

        NOTIFY_INFO_QUICK("Cheat injected successfully. The menu opens on " + Utils::getKeyName(MenuToggleKey));
        LOG_INFO("Cheat injected successfully. The menu opens on " + Utils::getKeyName(MenuToggleKey));

        while (CheatWork) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        LOG_INFO("Starting cleanup...");

        Config::SaveConfig();

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

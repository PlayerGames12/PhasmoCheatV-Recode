#include <Windows.h>
#include "Includes.h"
#include "globals.h"
#include "memory.h"
#include "main/config/config.h"
#include "libs/il2cpp/il2cpp.h"
#include "loader/entry.h"
#include "loader/proxy.h"
#include "main/discordrpc/discordrpc.h"

using namespace PhasmoCheatV;

HWND WaitForGameWindow()
{
    HWND hwnd = nullptr;

    while (!hwnd)
    {
        hwnd = FindWindowA(nullptr, "Phasmophobia");
        Sleep(200);
    }

    return hwnd;
}

void WaitForGameReady()
{
    while (!GetModuleHandleA("GameAssembly.dll"))
        Sleep(200);

    HWND hwnd = WaitForGameWindow();

    Sleep(2000);
}

LONG CALLBACK VehHandler(EXCEPTION_POINTERS* ep)
{
    if (ep->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
    {
        auto rip = ep->ContextRecord->Rip;
        auto addr = ep->ExceptionRecord->ExceptionInformation[1];

        char buf[128];
        wsprintfA(buf, "AV RIP=%p ADDR=%p\n", (void*)rip, (void*)addr);
        LOG_INFO(buf);
        OutputDebugStringA(buf);
    }

    return EXCEPTION_CONTINUE_SEARCH; // fall next
}

// Global module handle
static std::unique_ptr<Logger> loggerInstance;
static std::unique_ptr<Renderer> rendererInstance;
static std::unique_ptr<Hooking> hookingInstance;
static std::unique_ptr<FeatureHandler> featureInstance;
static PVOID g_VehHandle = nullptr;

// Main cheat thread
extern "C" __declspec(dllexport) DWORD WINAPI PhasmoCheatVThread()
{
    g_VehHandle = AddVectoredExceptionHandler(1, VehHandler);

    WaitForGameReady();
    bool hooksApplied = false;

    try {
        loggerInstance = std::make_unique<Logger>(Logger::Level::Call);
    }
    catch (...) {
        return 0;
    }

    // Initialize SDK
    if (!SDK::Initialize()) {
        LOG_ERROR("Failed to initialize SDK");
        goto finalize;
    }

    try {
        LanguageManager::Init();
        rendererInstance = std::make_unique<Renderer>();
        hookingInstance = std::make_unique<Hooking>();
        featureInstance = std::make_unique<FeatureHandler>();

        hookingInstance->OriginalPresent = rendererInstance->GetPresent();

        Config::LoadConfig();

        if (IsDebugging)
            LOG_WARN("The build is built with the IsDebugging flag in the true state, followed by the appearance of the console, as well as the execution of Test functions!");

        LOG_INFO("Game version: ", Utils::GetGameVersion());
		LOG_INFO("Engine version: ", Utils::GetUnityVersion());

        Discord::Initialize();

        /* 2.6-2.7 Diagnostics is currently disabled due to some issues, but it will be back in the future updates.
        if (Diagnostics::Init())
        {
            Diagnostics::Send("GameVersion", Utils::GetGameVersion());
            Diagnostics::Send("UnityVersion", Utils::GetUnityVersion());
        }
        else
            LOG_ERROR("VT_Diagnostics initialization failed.");
        */

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
        //AHKA(Player_StartKillingPlayer);
        //AHKA(Player_StartKillingPlayerNetworked);
        AHKA(Player_Start);
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
        AHKA(ServerManager_Ready);
        AHKA(DNAEvidence_GrabbedNetworked);
        AHKA(FallTeleportBox_OnTriggerEnter);
        AHKA(LightSwitch_Start);
        AHKA(LightningController_Start);
        AHKA(TarotCards_BreakItem);
        AHKA(RandomWeather_Start);
        AHKA(CursedItemsController_Awake);
        AHKA(LiftButton_AttemptUse);
        AHKA(GameController_PlayerDied);
        AHKA(Thermometer_HoldUse);
        AHKA(PhotonView_RPC);
        AHKA(ServerManager_LoadScene);
        AHKA(LiftButton_Update);
        AHKA(DNAEvidence_Start);
        AHKA(VoodooDollPin_Use);
        AHKA(Jackalope_Awake);
        AHKA(ScriptableRenderContext_Submit);
        AHKA(Player_BeginDeathSequence);
        AHKA(GameController_Awake);
        AHKA(RewardManager_Awake);
        AHKA(SceneManagement_Internal_SceneLoaded);
        AHKA(Key_GrabbedKey);

        // CosmeticsUnlocker hooks
#if COSMETICSUNLOCKER
#include "unlockcosmetics/dllmain_hooks.txt"
#endif

        PHK(HandCamera_MoveNext, Hooks::hkHandCamera_MoveNext); // Use PATTERN_HOOK

        auto& funcs_UpdateNightmareGraph = const_cast<std::vector<SDK::EMFData_UpdateNightMareGraph_t>&>(SDK::Get_EMFData_UpdateNightMareGraph_All());
        for (size_t i = 0; i < funcs_UpdateNightmareGraph.size(); i++)
        {
            hooking->AddHook("EMFData_UpdateNightMareGraph_" + std::to_string(i), reinterpret_cast<PVOID*>(&funcs_UpdateNightmareGraph[i]), reinterpret_cast<PVOID>(&Hooks::hkEMFData_UpdateNightMareGraph));
        }

        hookingInstance->ApplyHooks();
        hooksApplied = true;

        // only English!
        LOG_RELEASE(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, "Welcome, %s, to PhasmoCheatV\nPhasmophobia version: %s\n", Utils::GetPlayerName().c_str(), Utils::GetGameVersion().c_str());
        LOG_RELEASE(FOREGROUND_BLUE | FOREGROUND_INTENSITY, std::string(32, '-').c_str(), "\n");
        LOG_RELEASE(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, "Menu navigation:\n");
		LOG_RELEASE(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, "Press", Utils::getKeyName(MenuToggleKey), "to open / close the menu\n");
		LOG_RELEASE(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, "Press End to emergency exit cheat\n");
		LOG_RELEASE(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, "Press Home to reset menu open/close button\n");
		LOG_RELEASE(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, "Config folder: C:\\PhasmoCheatV\\configs\n");
        LOG_RELEASE(FOREGROUND_BLUE | FOREGROUND_INTENSITY, std::string(32, '-').c_str(), "\n");

        NOTIFY_INFO_QUICK(LANG("Menu_CheatInjected") + Utils::getKeyName(MenuToggleKey));
        LOG_INFO("Cheat injected successfully. The menu opens on " + Utils::getKeyName(MenuToggleKey));

        InGame::ghostAI = Utils::GetGhostAI();
        if (!InGame::ghostAI) LOG_INFO("Ghost not found with tag!");

        int presenceUpdateTimer = 0;

        while (CheatWork) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            if (++presenceUpdateTimer >= 150 && Globals::DiscordRPC)
            {
                Discord::UpdatePresence();
                presenceUpdateTimer = 0; 
            }
        }
    }
    catch (const std::exception& e) {
        LOG_ERROR(std::string("Exception in main thread: ") + e.what());
    }

    LOG_INFO("Starting cleanup...");

    try
    {
        Config::SaveConfig();

        if (rendererInstance) {
            ImGui::SaveIniSettingsToDisk((Utils::GetPhasmoCheatVDirectory() + "\\menu.ini").c_str());
        }
    }
    catch (...) {}

    Discord::Shutdown();

    if (hooksApplied && hookingInstance)
    {
        try
        {
            hookingInstance->RemoveHooks();
        }
        catch (...) {}
        hooksApplied = false;
    }

    hookingInstance.reset();
    rendererInstance.reset();
    featureInstance.reset();

    LOG_INFO("Cleanup completed");

finalize:
    if (loggerInstance)
        loggerInstance->ShutdownConsole();

    loggerInstance.reset();

    if (g_VehHandle)
    {
        RemoveVectoredExceptionHandler(g_VehHandle);
        g_VehHandle = nullptr;
    }

    FreeLibraryAndExitThread(globalModule, NULL);
    return 0;
}

// DLL entry point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);

        if (!IsProxyMode(hModule)) StartCheat(hModule);
        else StartCheat(hModule);

        break;
    }

    case DLL_PROCESS_DETACH:
    {
        CheatWork = false;
        Sleep(100);

        Proxy::Shutdown();
        break;
    }
    }

    return TRUE;
}
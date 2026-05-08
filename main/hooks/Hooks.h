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
		static void hkLevelController_Start(SDK::LevelController* levelController, SDK::MethodInfo* methodInfo);
		static void hkExitLevel_Exit(SDK::ExitLevel* exitLevel, void* photon, SDK::MethodInfo* methodInfo);
		static void hkGameController_Exit(SDK::GameController* gameController, void* photon, SDK::MethodInfo* methodInfo);
		static void hkPauseMenuController_Leave(SDK::PauseMenuController* pauseMenuController, SDK::MethodInfo* methodInfo);
		static void hkMapController_Start(SDK::MapController* mapController, SDK::MethodInfo* methodInfo);
		static void hkGhostAI_Start(SDK::GhostAI* ghostAI, SDK::MethodInfo* methodInfo);
		static void hkGhostAI_Update(SDK::GhostAI* ghostAI, SDK::MethodInfo* methodInfo);
		static void hkGhostAI_Hunting(SDK::GhostAI* ghostAI, bool isHunting, int obakeArrayID, void* photon, SDK::MethodInfo* methodInfo);
		static void hkEvidenceController_Start(SDK::EvidenceController* evidenceController, SDK::MethodInfo* methodInfo);
		static void hkEMFData_Start(SDK::EMFData* emfData, SDK::MethodInfo* methodInfo);
		static void hkPlayer_StartKillingPlayer(SDK::Player* player, SDK::MethodInfo* methodInfo);
		static std::nullptr_t hkPlayer_StartKillingPlayerNetworked(SDK::Player* player, bool b1, void* photon, SDK::MethodInfo* methodInfo);
		static void hkPlayer_Start(SDK::Player* player, SDK::MethodInfo* methodInfo);
		static void hkGhostInfo_SyncEvidence(SDK::GhostInfo* instance, int* evidence, void* info, SDK::MethodInfo* methodInfo);
		static void hkGhostInfo_SyncValuesNetworked(SDK::GhostInfo* instance, int ghostType, int ghostAge, bool isMale, int ghostFirstNameID, int ghostLastNameID, bool isShy, int deathLength, int favouriteRoomID, bool isWhisper, void* photonMessageInfo, SDK::MethodInfo* methodInfo);
		static void hkPhotonObjectInteract_Start(SDK::PhotonObjectInteract* photonObjectInteract, SDK::MethodInfo* methodInfo);
		static void hkFirstPersonController_Update(SDK::FirstPersonController* firstPersonController, SDK::MethodInfo* methodInfo);
		static void hkTarotCard_SetCard(SDK::TarotCard* instance, SDK::TarotCardType type, SDK::MethodInfo* methodInfo);
		static void hkPlayerStamina_Update(SDK::PlayerStamina* playerStamina, SDK::MethodInfo* methodInfo);
		static bool hkExitLevel_ThereAreAlivePlayersOutsideTheTruck(SDK::ExitLevel* exitLevel, SDK::MethodInfo* methodInfo);
		static void hkServerManager_KickPlayerNetworked(SDK::ServerManager* serverManager, bool isBanned, void* photon, SDK::MethodInfo* methodInfo);
		static void hkObjectiveManager_Update(SDK::ObjectiveManager* objectiveManager, SDK::MethodInfo* methodInfo);
		static int32_t hkLevelValues_GetInvestigationBonusReward(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo);
		static bool hkLevelValues_IsPerfectGame(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo);
		static int32_t hkMediaValues_GetRewardAmount(SDK::MediaValues* mediaValues, SDK::EvidenceQualityType qualityType, SDK::TierList mediaTier, SDK::MethodInfo* methodInfo);
		static void hkKey_Start(SDK::Key* key, SDK::MethodInfo* methodInfo);
		static void hkSaltShaker_Update(SDK::SaltShaker* saltShaker, SDK::MethodInfo* methodInfo);
		static void hkSaltSpot_SyncSalt(SDK::SaltSpot* saltSpot, void* photonMessageInfo, SDK::MethodInfo* methodInfo);
		static std::nullptr_t hkLevelSelectionManager_Start(SDK::LevelSelectionManager* levelSelectionManager, SDK::MethodInfo* methodInfo);
		static void hkApplication_CallLogCallback(SDK::String* logString, SDK::String* stackTrace, SDK::LogType type, bool invokedOnMainThread, SDK::MethodInfo* methodInfo);
		static void hkServerManager_Ready(SDK::ServerManager* serverManager, bool on, SDK::MethodInfo* methodInfo);
		static void hkDNAEvidence_GrabbedNetworked(SDK::DNAEvidence* dnaEvidence, SDK::MethodInfo* methodInfo);
		static void hkFallTeleportBox_OnTriggerEnter(SDK::FallTeleportBox* fallTeleportBox, SDK::Collider* collider, SDK::MethodInfo* methodInfo);
		static void hkLightSwitch_Start(SDK::LightSwitch* lightSwitch, SDK::MethodInfo* methodInfo);
		static void hkLightningController_Start(SDK::LightningController* lightningController, SDK::MethodInfo* methodInfo);
		static void hkTarotCards_GrabCard(SDK::TarotCards* tarotCards, SDK::MethodInfo* methodInfo);
		static void hkTarotCards_BreakItem(SDK::TarotCards* tarotCards, SDK::MethodInfo* methodInfo);
		static void hkRandomWeather_Start(SDK::RandomWeather* randomWeather, SDK::MethodInfo* methodInfo);
		static void hkEMFData_UpdateNightMareGraph(SDK::EMFData* emfData, SDK::MethodInfo* methodInfo);
		static void hkCursedItemsController_Awake(SDK::CursedItemsController* cursedItemsController, SDK::MethodInfo* methodInfo);
		static void hkLiftButton_AttemptUse(SDK::LiftButton* liftButton, void* photon, SDK::MethodInfo* methodInfo);
		static void hkGameController_PlayerDied(SDK::GameController* gameController, SDK::Player* player, SDK::MethodInfo* methodInfo);
		static void hkThermometer_HoldUse(SDK::Thermometer* thermometer, SDK::MethodInfo* methodInfo);
		static void hkPhotonView_RPC(SDK::PhotonView* photonView, SDK::String* methodName, SDK::RpcTarget target, void* parameters, SDK::MethodInfo* methodInfo);
		static void hkServerManager_LoadScene(SDK::ServerManager* serverManager, int32_t mapID, int32_t smallMapIndex, int32_t weather, SDK::PhotonMessageInfo* photonMessageInfo, SDK::MethodInfo* methodInfo);
		static void hkLiftButton_Update(SDK::LiftButton* liftButton, SDK::MethodInfo* methodInfo);
		static void hkDNAEvidence_Start(SDK::DNAEvidence* dnaEvidence, SDK::MethodInfo* methodInfo);
		static bool hkHandCamera_MoveNext(SDK::HandCamera* handCamera, SDK::MethodInfo* methodInfo);
		static void hkVoodooDollPin_Use(SDK::VoodooDollPin* voodooDolPin, void* doll, SDK::Player* pn_player, bool lastPin, bool isNoSanityUse, SDK::MethodInfo* methodInfo);
		static void hkJackalope_Awake(SDK::Jackalope* jackalope, SDK::MethodInfo* methodInfo);
		static bool hkEVPRecorder_CanAnswer(SDK::EVPRecorder* recorder, SDK::MethodInfo* methodInfo);
		static void hkScriptableRenderContext_Submit(SDK::ScriptableRenderContext* context, SDK::MethodInfo* methodInfo);
		static std::nullptr_t hkPlayer_StartDeathAnimation(SDK::Player* player, int32_t a1, bool a2, void* photon, SDK::MethodInfo* methodInfo);
	};
}

#pragma once
#include "main/sdk/sdk.h"

namespace PhasmoCheatV::InGame
{
	inline bool LiftButtonOpenedByCheat = false;
    inline bool FuseBoxSwitchedByCheat = false;
    inline std::mutex g_GameObjectCacheMutex;

    inline SDK::GhostAI* ghostAI = nullptr;
    inline SDK::LevelController* levelController = nullptr;
    inline SDK::Network* network = nullptr;
    inline SDK::MapController* mapController = nullptr;
    inline SDK::FuseBox* fuseBox = nullptr;
    inline SDK::EvidenceController* evidenceController = nullptr;
    inline SDK::GameObject* FBGO = nullptr; // FullBright GameObject
    inline SDK::EMFData* emfData = nullptr;
    inline std::vector<SDK::PhotonObjectInteract*> photonInstances;
    inline SDK::CursedItemsController* cursedItemsController = nullptr;
    inline std::vector<SDK::Key*> keys;
    inline std::vector<SDK::SaltShaker*> saltShakers;
    inline std::vector<SDK::LightSwitch*> lightSwitchs;
    inline SDK::LightningController* lightningController = nullptr;
    inline SDK::TarotCards* tarotCards = nullptr;
    inline SDK::RandomWeather* randomWeather = nullptr;
    inline SDK::LevelSelectionManager* levelSelectionManager = nullptr;
    inline SDK::HandCamera* handCamera = nullptr;
    inline SDK::DifficultySettings* difficultySettings = nullptr;
	inline std::vector<SDK::Jackalope*> jackalope;
	inline SDK::FirstPersonController* firstPersonController = nullptr;
    inline SDK::GameController* gameController = nullptr;
	inline SDK::ObjectiveManager* objectiveManager = nullptr;
    inline SDK::RewardManager* rewardManager = nullptr;
    inline std::unordered_map<std::string, SDK::GameObject*> g_GameObjectCache;
    inline std::vector<SDK::AWDoll*> awDolls;

    // Reset in-game pointers
    inline void Reset() {
		LiftButtonOpenedByCheat = false;
        FuseBoxSwitchedByCheat = false;

        ghostAI = nullptr;
        levelController = nullptr;
        network = nullptr;
        mapController = nullptr;
        fuseBox = nullptr;
        evidenceController = nullptr;
        FBGO = nullptr;
        emfData = nullptr;
		photonInstances.clear();
        keys.clear();
        saltShakers.clear();
        cursedItemsController = nullptr;
        lightSwitchs.clear();
        lightningController = nullptr;
        tarotCards = nullptr;
        randomWeather = nullptr;
        levelSelectionManager = nullptr;
        handCamera = nullptr;
        difficultySettings = nullptr;
		firstPersonController = nullptr;
        jackalope.clear();
        gameController = nullptr;
		objectiveManager = nullptr;
        rewardManager = nullptr;
		g_GameObjectCache.clear();
        awDolls.clear();
    }
}
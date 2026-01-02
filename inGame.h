#pragma once
#include "main/sdk/sdk.h"

namespace PhasmoCheatV::InGame
{
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

    // Reset in-game pointers
    inline void Reset() {
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
    }
}
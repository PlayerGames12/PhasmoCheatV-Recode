#include "mapmodifier.h"
using namespace PhasmoCheatV::Features::Map;

constexpr int32_t mapIds[] = {
    -1,  // Random
    4,   // Tanglewood Drive
    6,   // Edgefield Road
    7,   // Ridgeview Court
    0,   // none
    10,  // Grafton Farmhouse
    12,  // Willow Street
    15,  // Point Hope
    8,   // Brownstone High School
    9,   // Bleasdale Farmhouse
    5,   // Sunny Meadows
    0,   // none
    11,  // Prison
    13,  // Maple Lodge Campsite
    14   // Camp Woodwind
};

const char* mapItems[] = {
    "Random",
    "Tanglewood Drive",
    "Edgefield Road",
    "Ridgeview Court",
    "Nell's Diner",
    "Grafton Farmhouse",
    "Willow Street",
    "Point Hope",
    "Brownstone High School",
    "Bleasdale Farmhouse",
    "Sunny Meadows",
    "Sunny Meadows Restricted",
    "Prison",
    "Maple Lodge Campsite",
    "Camp Woodwind"
};

MapModifier::MapModifier() : FeatureCore("Map Modifier", TYPE_MAP)
{
    DECLARE_CONFIG(GetConfigManager(), "CustomMaxLight", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "MaxLight", int32_t, 10);
    DECLARE_CONFIG(GetConfigManager(), "AutoSelectMap", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "AutoVoteMapId", int32_t, -1);
}

void MapModifier::OnMenuRender()
{
    bool AutoSelectMap = CONFIG_BOOL(GetConfigManager(), "AutoSelectMap");
    int32_t AutoVoteMapId = CONFIG_INT(GetConfigManager(), "AutoVoteMapId");

    SDK::Map* mapInstance = Utils::GetMap();
    if (mapInstance)
    {
        std::string CurrentMapName = Utils::UnityStrToSysStr(*mapInstance->Fields.mapName);
        ImGui::Text("Current Map: %s", CurrentMapName.c_str());
    }

    if (ImGui::Checkbox("Auto Select Map", &AutoSelectMap))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "AutoSelectMap", bool, AutoSelectMap);
    }

    if (AutoSelectMap)
    {
        int currentItem = 0;
        for (int i = 0; i < IM_ARRAYSIZE(mapIds); i++)
        {
            if (mapIds[i] == AutoVoteMapId)
            {
                currentItem = i;
                break;
            }
        }

        if (ImGui::Combo("Select Map", &currentItem, mapItems, IM_ARRAYSIZE(mapItems)))
        {
            int32_t newMapId = mapIds[currentItem];
            SET_CONFIG_VALUE(GetConfigManager(), "AutoVoteMapId", int32_t, newMapId);
            selectedAutoVoteMap = static_cast<MapIdsAutoVote>(newMapId);
        }
    }

    bool enabled = IsActive();
    bool CustomMaxLight = CONFIG_BOOL(GetConfigManager(), "CustomMaxLight");
    int32_t MaxLight = CONFIG_INT(GetConfigManager(), "MaxLight");

    if (ImGui::Checkbox("Enable Map Modifier", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled)
    {
        if (ImGui::Checkbox("Custom max lights", &CustomMaxLight))
            SET_CONFIG_VALUE(GetConfigManager(), "CustomMaxLight", bool, CustomMaxLight);
        if (CustomMaxLight)
        {
            if (ImGui::SliderInt("Max lights", &MaxLight, 1, 100))
                SET_CONFIG_VALUE(GetConfigManager(), "MaxLight", int32_t, MaxLight);
        }
    }
}

void MapModifier::MapModifierMain()
{
    if (IsActive() && CONFIG_BOOL(GetConfigManager(), "CustomMaxLight") && InGame::fuseBox)
    {
        InGame::fuseBox->Fields.maxLights = CONFIG_INT(GetConfigManager(), "MaxLight");
    }
}

std::atomic<bool> autoVoteRunning{ false };

void MapModifier::MapModifierMainAutoVote(SDK::LevelSelectionManager* levelSelectionManager)
{
    if (autoVoteRunning.load())
        return;

    if (!CONFIG_BOOL(GetConfigManager(), "AutoSelectMap"))
        return;

    autoVoteRunning.store(true);
    std::thread([this, levelSelectionManager]() {
        auto start = std::chrono::steady_clock::now();

        while (true)
        {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();

            if (elapsed >= 5000)
            {
                if (levelSelectionManager)
                {
                    int32_t mapId = CONFIG_INT(GetConfigManager(), "AutoVoteMapId");
                    SDK::LevelSelectionManager_VoteMap(levelSelectionManager, mapId, nullptr);
                }
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        autoVoteRunning.store(false);
        }).detach();
}

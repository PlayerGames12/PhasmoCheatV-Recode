#pragma once
#include "MouseLook.h"
#include "sdk.h"

namespace SDK
{
    struct LevelValuesFields
    {
        MonoBehaviourFields MonoBehaviourFields;
        bool stayInServerRoom;
        bool inGame;
        bool setupPhase;
        bool isTutorial;
        bool isPublicServer;
        int maxRoomPlayers;
        int smallMapIndex;
        void* Field7;
        Difficulty* currentDifficulty;
        Difficulty* previousDifficulty;
        Map* Map;
        void* mainObjective;
        void* sideObjectives;
        void* dnaObjective;
        void* Field14;
        void* Field15;
        int eventItemsCollected;
        float Field17;
        void* equipmentLoadout;
        void* currentWeather;
        bool isMenuMusicMuted;
        void* OnGraphicsSettingsChanged;
    };

    struct LevelValues
    {
        void* Clazz;
        void* Monitor;
        LevelValuesFields Fields;
    };

    DEC_MET(LevelValues_get_Instance, LevelValues* (*)(MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelValues", "get_Instance", 0);
    DEC_MET(LevelValues_get_map, Map* (*)(LevelValues* levelValues, MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelValues", "get_map", 0);
    DEC_MET(LevelValues_GetInvestigationBonusReward, int(*)(LevelValues* levelValues, MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelValues", "GetInvestigationBonusReward", 0);
    DEC_MET(LevelValues_IsPerfectGame, bool(*)(LevelValues* levelValues, MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelValues", "IsPerfectGame", 0);
}
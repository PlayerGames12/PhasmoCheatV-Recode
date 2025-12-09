#pragma once
#include "sdk.h"

namespace SDK
{
    struct LevelStatsFields
    {
        int diedAmount;
        int revivedAmount;
        float distanceWalked;
        float distanceSprinted;
        float sanityGained;
        float sanityLost;
        float timeSpentInDark;
        float timeSpentInLight;
        float timeSpentInGhostsRoom;
        float timeSpentInvestigating;
        float timeSpentInTruck;
        float timeSpentBeingChased;
        int photosTaken;
        int videosTaken;
        int soundsTaken;
        int ghostsRepelled;
        int phrasesRecognized;
        bool ghostSuccessfullyGuessed;
        int objectivesCompleted;
        int objectivesFailed;
        int moneyEarned;
        int moneySpent;
        int itemsBought;
        int itemsLost;
        int cursedPossessionsUsed;
        int cursedHuntsTriggered;
        bool collectedBone;
        float averageFPS;
        float ghostDistanceTravelled;
        int itemsThrown;
        int objectsUsed;
        int doorsMoved;
        int lightsSwitched;
        int fuseboxToggles;
        int roomsChanged;
        int abilitiesUsed;
        float totalHuntTime;
        float timeInFavouriteRoom;
        float timeOutFavouriteRoom;
        int ghostEvents;
        int ghostHunts;
        int ghostInteractions;
        String* boneRoom;
        int shortRoams;
        int longRoams;
        float timeSpentChasingPlayers;
        void* ghost;
        void* Authentication;
    };

    struct LevelStats
    {
        void* Clazz;
        void* monitor;
        LevelStatsFields Fields;
    };


    DEC_MET(LevelStats_get_Instance, LevelStats* (*)(MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelStats", "get_Instance", 0);
}

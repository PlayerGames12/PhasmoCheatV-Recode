#pragma once
#include "sdk.h"

namespace SDK
{
    struct MapFields
    {
        char pad_000[8]; // Padding for ScriptableObject base fields
        int32_t levelType; // Enum, 4 bytes (was void* - wrong)
        int32_t levelSize; // Enum, 4 bytes (was void* - wrong)
        String* mapName;
        String* descriptionLocaliseID; // Fixed typo: LoacaliseID -> LocaliseID
        int32_t totalRooms;
        int32_t totalFloors;
        void* mapSelectSprite; // Sprite*
        void* loadingSpriteLarge; // Sprite*
        void* loadingSpriteSmall; // Sprite* (was Sprite3 - probably typo, added missing)
        String* sceneName;
        String* easterSceneName;
        String* halloweenSceneName;
        String* holidaySceneName;
        int32_t uniqueMapID;
        int32_t activityID;
        int32_t unlockAtLevel;
    };

	struct Map
	{
		void* Clazz;
		void* Monitor;
		MapFields Fields;
	};
}
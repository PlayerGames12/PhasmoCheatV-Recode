#pragma once
#include "sdk.h"

namespace SDK
{

    enum class DifficultyValueType : int32_t
    {
        None,
        Low,
        Medium,
        High,
        VeryHigh
    };

    enum class DifficultyWeatherValueType : int32_t
    {
        Random,
        LightRain,
        HeavyRain,
        Snow,
        Wind,
        Clear,
        Fog,
        Sunrise,
        BloodMoon
    };

    enum class DifficultyFuseBoxValueType : int32_t
    {
        Broken,
        Off,
        On
    };

    enum class DiffType : int32_t
    {
        Amateur,
        Intermediate,
        Professional,
        Nightmare,
        Insanity,
        Challenge,
        Custom,
        Custom2,
        Custom3,
        ApocalypseBronze,
        ApocalypseSilver,
        ApocalypseGold
    };

    enum class DiffCursedItems : int32_t
    {
        none,
        tarotCards,
        ouijaBoard,
        mirror,
        musicBox,
        summoningCircle,
        voodooDoll,
        monkeyPaw
    };

    struct DifficultyFields
    {
        char pad_000[0x8];
        DiffType difficulty;
        const char* nameKey;
        const char* descriptionKey;
        int32_t requiredLevel;
        int32_t sanityPillRestore;
        int32_t startingSanity;
        float sanityDrain;
        int32_t sprinting;
        bool flashlights;
        bool loseItemsOnDeath;
        char pad_001[2];
        float playerSpeed;
        int32_t evidenceGiven;
        DifficultyValueType changingFav;
        DifficultyValueType interaction;
        DifficultyValueType eventFreq;
        DifficultyValueType huntDuration;
        int32_t gracePeriod;
        float fingerprintChance;
        int32_t fingerprintDuration;
        bool friendlyGhost;
        char pad_002[3];
        DifficultyValueType killsExtend;
        DifficultyValueType roamingFreq;
        float ghostSpeed;
        int32_t setupTime;
        DifficultyWeatherValueType selectedWeather;
        DifficultyValueType amountDoorsOpen;
        DifficultyValueType amountHidingPlaces;
        bool sanityMonitor;
        bool activityMonitor;
        bool fuseBoxVisible;
        char pad_003;
        DifficultyFuseBoxValueType fuseBoxStart;
        int32_t cursedCount;
        void* chosenCursed;
        float overrideMultiplier;
        DifficultyWeatherValueType actualWeather;
        void* actualCursed;
        void* itemTiers;
        const char* mapName;
        void* nameLocalisedOverrides;
        void* descriptionLocalisedOverrides;
    };

    struct Difficulty
    {
        void* Clazz;
        void* Monitor;
        DifficultyFields Fields;
    };
}
#pragma once
#include "sdk.h"

namespace SDK
{
    struct Player;

    struct PlayerStaminaFields
    {
        MonoBehaviourFields MonoBehaviourFields;
        void* OutOfStaminaSource;
        void* OutOfBreathMale;
        void* OutOfBreathFemale;
        Player* Player;
        bool MaleSoundsOverride;
        bool FemaleSoundsOverride;
        bool isMoving;
        bool canSprint;
        bool isSprinting;
        bool isWalking;
        bool Draining;
        bool CanDrainStamina;
        bool NewIsSprinting;
        bool NewIsWalking;
        bool StaminaDrained;
        bool Delayed;
        float CurrentStaminaRecharge;
        float CurrentStamina;
        float RestoreDelay;
        void* OnStaminaDrained;
        void* OnStaminaRestored;
    };

    struct PlayerStamina
    {
        void* Clazz;
        void* Monitor;
        PlayerStaminaFields Fields;
    };

    DEC_MET(PlayerStamina_Update, void (*)(PlayerStamina* playerStamina, MethodInfo* methodInfo), "Assembly-CSharp", "", "PlayerStamina", "Update", 0);
}
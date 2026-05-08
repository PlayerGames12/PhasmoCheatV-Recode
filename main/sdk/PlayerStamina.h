#pragma once
#include "sdk.h"

namespace SDK
{
    struct Player;

    struct PlayerStaminaFields
    {
        MonoBehaviourFields MonoBehaviourFields; // 0x0 - 0x20
        void* player;
        void* networkedStamina;
        bool unk_30;
        bool unk_31;
        bool unk_32;
        bool unk_33;
        bool unk_34;
        bool unk_35;
        bool unk_36;
        bool unk_37;
        bool unk_38;
        bool unk_39;
        char pad_3A[0x2];
        float CurrentStaminaRecharge;
        float CurrentStamina;
        float RestoreDelay;
        void* staminaDrainedEvent;
        void* staminaRestoredEvent;
    };

    struct PlayerStamina
    {
        void* Clazz;
        void* Monitor;
        PlayerStaminaFields Fields;
    };

    DEC_MET(PlayerStamina_Update, void (*)(PlayerStamina* playerStamina, MethodInfo* methodInfo), "Assembly-CSharp", "", "PlayerStamina", "Update", 0);
}
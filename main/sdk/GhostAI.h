#pragma once
#include "sdk.h"

namespace SDK
{
    struct GhostModel;
    struct Player;
    struct GhostActivity;

    enum class GhostState : int32_t
    {
        Idle,
        Wander,
        Hunting,
        FavoriteRoom,
        Light,
        Door,
        Throwing,
        FuseBox,
        Appear,
        DoorKnock,
        WindowKnock,
        CarAlarm,
        Flicker,
        CCTV,
        RandomEvent,
        GhostAbility,
        Mannequin,
        TeleportObject,
        Interact,
        SummoningCircle,
        MusicBox,
        Dots,
        Salt
    };


    struct GhostAIFields
    {
        MonoBehaviourPunFields MonoBehaviourPunFields; // 0x0 - 0x28

        void* stateMachine;            // 0x28
        GhostState currentState;          // 0x30
        GhostInfo* GhostInfo;          // 0x38
        void* NavMeshAgent;            // 0x40
        void* GhostAudio;              // 0x48
        void* GhostInteraction;        // 0x50
        GhostActivity* GhostActivity;  // 0x58
        GhostModel* currentModel;      // 0x60
        GhostModel* HalloweenModel;    // 0x68
        GhostModel* HolidayModel;      // 0x70
        GhostModel* EasterModel;       // 0x78
        void* GhostModels0;            // 0x80
        void* GhostModels1;            // 0x88

        int32_t currrentShadowCastingMode; // 0x90
        char pad_94[0x4];                  // до 0x98

        void* ghostBreadcrumbs;       // 0x98
        float breadcrumbTimer;        // 0xA0
        float FieldA4;                // 0xA4

        void* SanityDrainer;          // 0xA8
        void* LOSSensor;              // 0xB0

        bool Field14;                 // 0xB8
        char pad_B9[0x7];             // до 0xC0

        Transform* raycastPoint;          // 0xC0
        Transform* huntingRaycastPoint;   // 0xC8
        Transform* feetRaycastPoint;      // 0xD0

        float defaultSpeed;           // 0xD8
        float saltSpeedMultiplier;    // 0xDC
        float incenseSpeedMultiplier; // 0xE0
        float FieldE4;                // 0xE4

        bool Field24;                 // 0xE8
        bool Field25;                 // 0xE9
        char pad_EA[0x2];             // до 0xEC

        Vector3 Field26;              // 0xEC
        void* Field27;                // 0xF8

        bool Field28;                 // 0x100
        bool Field29;                 // 0x101
        bool Field30;                 // 0x102
        bool Field301;                // 0x103
        bool FieldExtra;              // 0x104
        bool FieldExtra2;             // 0x105
        char pad_106[0x2];            // до 0x108

        void* WhiteSage;              // 0x108
        float Field32;                // 0x110
        float Field114;               // 0x114

        bool Field33;                 // 0x118
        bool Field34;                 // 0x119
        bool isTrapped;               // 0x11A
        char pad_11B[0x5];            // до 0x120

        Player* BansheeTarget;        // 0x120
        int32_t onryoCandleBlowCounter; // 0x128
        Vector3 Field38;              // 0x12C

        bool FieldAfterVec;           // 0x138
        char pad_139[0x7];            // до 0x140

        void* Field39;                // 0x140
        void* Field40;                // 0x148
        void* Field41;                // 0x150

        int32_t Field42;              // 0x160
        int32_t Field43;              // 0x164
        int32_t Field44;              // 0x168
        int32_t Field45;              // 0x16C
        int32_t Field46;              // 0x170
        char pad_174[0x4];            // до 0x178

        void* Field47;                // 0x178
        void* Field48;                // 0x180
        void* Field49;                // 0x188

        float Field50;                // 0x190
        void* Field51;                // 0x198
    };

    struct GhostAI
    {
        void* Clazz;
        void* Monitor;
        GhostAIFields Fields;
    };

    DEC_MET(GhostAI_Appear, void(*)(GhostAI* ghostAI, int effectIndex, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostAI", "Appear", 1);
    DEC_MET(GhostAI_Hunting, void(*)(GhostAI* ghostAI, bool isHunting, int obakeArrayID, void* PhotonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostAI", "Hunting", 3);
    DEC_MET(GhostAI_Start, void(*)(GhostAI* ghostAI, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostAI", "Start", 0);
    DEC_MET(GhostAI_Update, void(*)(GhostAI* ghostAI, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostAI", "Update", 0);
    DEC_MET(GhostAI_ChangeState, void(*)(GhostAI* ghostAI, GhostState ghostState, void* photonObjectInteract, void* photonObjectInteractArray, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostAI", "ChangeState", 3);
    DEC_MET(GhostAI_SetGhostModel, void(*)(GhostAI* ghostAI, GhostModel* ghostModel, bool resetHuntSound, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostAI", "SetGhostModel", 2);
}

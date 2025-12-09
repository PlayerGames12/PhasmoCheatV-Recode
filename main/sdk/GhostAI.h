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
        MonoBehaviourPunFields MonoBehaviourPunFields;
        void* stateMachine;
        GhostState currentState;
        GhostInfo* GhostInfo;
        void* NavMeshAgent;
        void* GhostAudio;
        void* GhostInteraction;
        GhostActivity* GhostActivity;
        GhostModel* NormalModel;
        GhostModel* HalloweenModel;
        GhostModel* HolidayModel;
        GhostModel* EasterModel;
        void* GhostModels0;
        void* GhostModels1;
        bool canSwapModel;
        int32_t currrentShadowCastingMode;
        void* ghostBreadcrumbs;
        float breadcrumbTimer;
        void* SanityDrainer;
        bool Field14;
        int32_t LayerMask;
        Transform* raycastPoint;
        Transform* huntingRaycastPoint;
        Transform* feetRaycastPoint;
        float defaultSpeed;
        float saltSpeedMultiplier;
        float incenseSpeedMultiplier;
        bool Field24;
        bool Field25;
        Vector3 Field26;
        void* Field27;
        bool Field28;
        bool Field29;
        bool Field30;
        bool Field301;
        void* WhiteSage;
        float Field32;
        bool Field33;
        bool Field34;
        bool isTrapped;
        Player* BansheeTarget;
        int32_t onryoCandleBlowCounter;
        Vector3 Field38;
        void* Field39;
        void* Field40;
        void* Field41;
        int32_t Field42;
        int32_t Field43;
        int32_t Field44;
        int32_t Field45;
        int32_t Field46;
        void* Field47;
        void* Field48;
        void* Field49;
        float Field50;
        void* Field51;
        void* Field52;
        void* Field53;
        void* Field54;
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

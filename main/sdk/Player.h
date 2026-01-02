#pragma once
#include "sdk.h"

namespace SDK
{
	struct PlayerSanity;
	struct PlayerStamina;
	struct LevelRoom;
	struct FirstPersonController;
    struct Animator;

    struct PlayerFields
    {
        MonoBehaviourFields MonoBehaviourFields;
        void* PhotonView;
        bool IsDead;
        bool Field1;
        bool Field2;
        int32_t modelId;
        void* PlayerCharacter;
        void* ClosetZone;
        GameObject* headObject;
        Transform* Field6;
        void* KeyInfoList;
        Camera* Camera;
        LevelRoom* LevelRoom;
        Transform* mapIcon;
        void* PhotonObjectInteract1;
        void* PhotonObjectInteract2;
        void* GameObjectArray;
        void* Field14;
        int32_t LayerMask;
        void* HeadMountedSocket;
        void* PlayerLOSTargetArray;
        Transform* Field18;
        GameObject* GameObject2;
        void* DeadPlayer;
        PlayerSanity* PlayerSanity;
        void* PlayerStats;
        void* FootstepController;
        void* JournalController;
        void* RendererArray;
        bool Field26;
        void* PlayerAudio;
        void* PlayerGraphics;
        void* PlayerSensors;
        PlayerStamina* PlayerStamina;
        float Field30;
        bool Field31;
        void* PhysicsCharacterController;
        void* AudioListener;
        FirstPersonController* FirstPersonController;
        void* PCPropGrab;
        void* DragRigidbodyUse;
        void* PCCanvas;
        void* PCCrouch;
        void* PCMenu;
        void* PCControls;
        void* PCFlashlight;
        Animator* Animator;
        void* PlayerInput;
        void* PCItemSway1;
        void* PCItemSway2;
        Transform* Field46;
        void* XRBaseInteractor1;
        void* XRBaseInteractor2;
        Transform* Field49;
        void* VRMovementSettings;
        void* VRBelt;
        void* XRSocketInteractor1;
        void* XRSocketInteractor2;
        void* TrailerCamera;
        void* VRLoading;
    };

	struct Player
	{
		void* Clazz;
		void* Monitor;
		PlayerFields Fields;
	};

	struct PlayerArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds;
		void* MaxLength;
		Player* Vector[65535];
	};

	struct __declspec(align(8)) ListPlayerFields
	{
		PlayerArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot;
	};

	struct ListPlayer
	{
		void* Clazz;
		void* Monitor;
		ListPlayerFields Fields;
	};

    DEC_MET(Player_KillPlayer, void(*)(Player* player, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "KillPlayer", 0);
    DEC_MET(Player_StartKillingPlayer, void(*)(Player* player, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "StartKillingPlayer", 0);
    DEC_MET(Player_StartKillingPlayerNetworked, std::nullptr_t(*)(Player* player, bool revive, void* photonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "StartKillingPlayerNetworked", 2);
    DEC_MET(Player_Teleport, void(*)(Player* player, Vector3 position, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "Teleport", 1);
    DEC_MET(Player_Start, void(*)(Player* player, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "Start", 0);
    DEC_MET(Player_ToggleFreezePlayer, void(*)(Player* player, bool freeze, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "ToggleFreezePlayer", 1);
    DEC_MET(Player_RevivePlayer, void(*)(Player* player, bool b1, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "RevivePlayer", 1);
    DEC_MET(Player_Revive, std::nullptr_t(*)(Player* player, void* photonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "Revive", 1);
    DEC_MET(Player_SpawnDeadBodyNetworked, void(*)(Player* player, PhotonMessageInfo* photonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "SpawnDeadBodyNetworked", 1);
}

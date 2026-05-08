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
        MonoBehaviourPunFields MonoBehaviourPunFields;
        bool IsDead;
        bool Field1;
        bool Field2;
        void* ClosetZone;
        GameObject* headObject;
        void* KeyInfoList;
        LevelRoom* LevelRoom;
        Transform* mapIcon;
        void* PhotonObjectInteract1;
        void* PhotonObjectInteract2;
        void* LayerMask;
        void* HeadMountedSocket;
        void* PlayerLOSTargetArray;
        Transform* aiTargetPoint;
        PlayerSanity* PlayerSanity;
        void* PlayerStats;
        void* FootstepController;
        bool Field26;
        void* wristwatch; // 0.17.0.0
        void* RendererArray;
        void* JournalController;
        void* GameObject2;
        void* DeadPlayer;
        void* PlayerAudio;
        PlayerStamina* PlayerStamina;
        void* NetworkedCrouch; // 0.17.0.0
        void* NetworkedPropGrab; // 0.17.0.0
        void* PlayerCharacterAnimations; // 0.17.0.0
        bool Field31;
        LocalPlayer* LocalPlayer; // 0.17.0.0
        void* RigLayer1; // 0.17.0.0
        void* RigLayer2; // 0.17.0.0
        void* PlayerCharacter; // 0.17.0.0
        Animator* Animator;
        void* FixedJoint; // 0.17.0.0
        void* EquipmentGrabIKController; // 0.17.0.0
        void* IKFOVController; // 0.17.0.0
        void* CapsuleCollider; // 0.17.0.0
        void* PlayerCosmetics; // 0.17.0.0
        bool Field_0x150; // 0.17.0.0
        void* Evidence; // 0.17.0.0
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

    DEC_MET(Player_Start, void(*)(Player* player, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "Start", 0);
    DEC_MET(Player_StartDeathAnimation, std::nullptr_t(*)(Player* player, int32_t a1, bool a2, void* message, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "StartDeathAnimation", 3);
}

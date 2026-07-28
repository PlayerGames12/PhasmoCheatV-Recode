#pragma once
#include "sdk.h"

namespace SDK
{
	struct PlayerSanity;
	struct PlayerStamina;
	struct LevelRoom;
	struct FirstPersonController;
    struct Animator;

    enum deathType : int32_t
    {
        HangedMan,
        SnappedNeck
    };

    struct PlayerFields
    {
        MonoBehaviourPunFields MonoBehaviourPunFields;
        bool IsDead;
        bool Field1; // idk, but maybe isDyingLocally
        bool Field2;
        char pad_000[0x5];
        void* ClosetZone;
        void* hidingSpot;
        GameObject* headObject;
        void* KeyInfoList;
        LevelRoom* LevelRoom;
        Transform* mapIcon;
        void* PhotonObjectInteract1;
        void* PhotonObjectInteract2;
        int32_t LayerMask;
        char pad_001[0x4];
        void* HeadMountedSocket;
        void* PlayerLOSTargetArray;
        Transform* aiTargetPoint;
        PlayerSanity* PlayerSanity;
        void* PlayerStats;
        void* FootstepController;
        bool Field26;
        char pad_002[0x7];
        void* wristwatch;
        void* ridgidBody;
        void* RendererArray;
        void* JournalController;
        void* GameObject2;
        void* DeadPlayer;
        void* PlayerAudio;
        void* networkedStamina;
        void* NetworkedCrouch;
        void* NetworkedPropGrab;
        void* PlayerCharacterAnimations;
        bool Field31;
        char pad_003[0x7];
        LocalPlayer* LocalPlayer;
        void* RigLayer1;
        void* RigLayer2;
        void* PlayerCharacter;
        Animator* Animator;
        void* FixedJoint;
        void* EquipmentGrabIKController;
        void* IKFOVController;
        void* CapsuleCollider;
        void* PlayerCosmetics;
        bool Field_0x160;
        char pad_004[0x7];
        void* Evidence;
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
		Player* Vector[1];
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
    DEC_MET(Player_BeginDeathSequence, void(*)(Player* player, deathType deadType, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "BeginDeathSequence", 1);
    DEC_MET(Player_SetHeadTransform, void(*)(Player* player, Vector3 position, Quaternion rotation, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "SetHeadTransform", 2);
	DEC_MET(Player_SetRotation, void(*)(Player* player, Quaternion rotation, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "SetRotation", 1);
    DEC_MET(Player_NotifyOfDeathEnd, void(*)(Player* player, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "NotifyOfDeathEnd", 0);
    DEC_MET(Player_NotifyOfDeathStart, void(*)(Player* player, void* photonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "NotifyOfDeathStart", 1);
}

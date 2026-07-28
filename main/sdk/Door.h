#pragma once
#include "sdk.h"

namespace SDK
{
	struct HingeDoor;
	struct PhotonView;

	struct DoorFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		bool locked;
		bool closed;
		bool hasBeenGrabbedByPlayer;
		char pad_000[0x5];
		void* DoorLockClips;
		void* DoorUnlockClips;
		void* Field28;
		void* Field30;
		void* Field38;
		void* Field40;
		void* Field48;
		float ClosedVolume;
		float UnlockVolume;
		void* LoopSource;
		void* Field60;
		void* Field68;
		bool Field70;
		bool Field71;
		bool Field72;
		bool Field73;
		char pad_001[0x4];
		PhotonView* photonView;
		Rigidbody* Rigidbody;
		void* Field88;
		void* Field90;
		Collider* col;
		float FieldA0;
		char pad_002[0x4];
		void* noise;
		void* FieldB0;
		bool useForceInsteadOfAnimations;
		char pad_003[0x3];
		int32_t FieldBC;
		Vector3 FieldC0;
		Vector3 Axis;
		Vector3 forwardDirection;
		char pad_004[0x4];
		void* FieldE8;
		void* FieldF0;
		KeyType keyType;
		char pad_005[0x4];
		void* hutnCollider;
		void* collideWithColliders;
		float closeDoorDistance;
		char pad_006[0x4];
		void* Field118;
		void* Field120;
		bool Field128;
		char pad_007[0x3];
		float loopSoundVelocityThreshold;
		float loopVolumeMultiplier;
		char pad_008[0x4];
		void* Field138;
		bool useGravityForDoorMovement;
		bool Field141;
		char pad_009[0x6];
		void* Field148;
		float Field150;
		float Field154;
		void* Field158;
		float Field160;
		char pad_010[0x4];
	};

	struct Door
	{
		void* Clazz;
		void* Monitor;
		DoorFields Fields;
	};

	struct DoorArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds;
		uint32_t MaxLength;
		Door* Vector[1];
	};

	DEC_MET(Door_DisableOrEnableCollider, void(*)(Door* door, bool collisionEnabled, MethodInfo* methodInfo), "Assembly-CSharp", "", "Door", "DisableOrEnableCollider", 1);
	DEC_MET(Door_DisableOrEnableDoor, void(*)(Door* door, bool activate, bool takeOwnership, MethodInfo* methodInfo), "Assembly-CSharp", "", "Door", "DisableOrEnableDoor", 2);
	DEC_MET(Door_LockDoorForTime, void(*)(Door* door, float time, bool locked, MethodInfo* methodInfo), "Assembly-CSharp", "", "Door", "LockDoorForTime", 2);
	DEC_MET(Door_OpenDoor, void(*)(HingeDoor* door, bool a1, float strenght, bool a3, MethodInfo* methodInfo), "Assembly-CSharp", "", "HingeDoor", "OpenDoor", 3);
	DEC_MET(Door_LevelControllerOpenDoor, void(*)(HingeDoor* door, bool a1, float strenght, MethodInfo* methodInfo), "Assembly-CSharp", "", "HingeDoor", "LevelControllerOpenDoor", 2);
}
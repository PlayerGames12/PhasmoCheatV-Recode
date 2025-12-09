#pragma once
#include "sdk.h"

namespace SDK
{
	struct DoorFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		bool Field0;
		bool Field1;
		bool Field2;
		void* DoorLockClips;
		void* DoorUnlockClips;
		void* Field3;
		void* Field4;
		float ClosedVolume;
		float UnlockVolume;
		void* LoopSource;
		void* Field5;
		void* Field6;
		bool Field7;
		bool Field8;
		bool Field9;
		void* Field10;
		Rigidbody* Rigidbody;
		void* Field11;
		void* Field12;
		void* Field13;
		float Field14;
		void* Noise;
		void* Field15;
		void* Field16;
		bool IsDoorRotationBackwards;
		int32_t Field17;
		int32_t Field18;
		int32_t Axis;
		bool SlideForwards;
		Vector3 Field19;
		Vector3 Field20;
		Vector3 ForwardDirection;
		void* Field21;
		int32_t Field22;
		void* HuntCollider;
		void* ClothDoor;
		Transform* trans;
		float Field24;
		void* CollideWithColliders;
		float CloseDoorDistance;
		void* Field25;
		void* Field26;
		bool Field27;
		float LoopSoundVelocityThreshold;
		float LoopVolumeMultiplier;
		void* Field28;
		float Field29;
		float Field30;
		float Field31;
		float Field32;
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
		void* MaxLength;
		Door* Vector[65535];
	};

	DEC_MET(Door_DisableOrEnableCollider, void(*)(Door* door, bool collisionEnabled, MethodInfo* methodInfo), "Assembly-CSharp", "", "Door", "DisableOrEnableCollider", 1);
	DEC_MET(Door_DisableOrEnableDoor, void(*)(Door* door, bool activate, bool takeOwnership, MethodInfo* methodInfo), "Assembly-CSharp", "", "Door", "DisableOrEnableDoor", 2);
	DEC_MET(Door_LockDoorForTime, void(*)(Door* door, float time, bool locked, MethodInfo* methodInfo), "Assembly-CSharp", "", "Door", "LockDoorForTime", 2);
}

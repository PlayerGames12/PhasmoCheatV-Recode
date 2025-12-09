#pragma once
#include "sdk.h"

namespace SDK
{
	struct CapsuleCollider;
	struct Collider;

	struct PhysicsCharacterControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		RaycastHit Field0;
		Vector3 Field1;
		float Field2;
		bool Field3;
		Vector3 Field4;
		bool Field5;
		float Field6;
		int32_t Field7;
		int32_t Field8;
		int32_t Field9;
		void* overlapCapsuleColliders;
		void* Field12;
		RaycastHit Field13;
		Vector3 Field14;
		Vector3 Field15;
		Rigidbody* Rigidbody;
		CapsuleCollider* CapsuleCollider;
		int32_t MaxIterationCount;
		int32_t NumPenetrationProbes;
		float MinMoveDistance;
	};

	struct PhysicsCharacterController
	{
		void* Clazz;
		void* Monitor;
		PhysicsCharacterControllerFields Fields;
	};
}

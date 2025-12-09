#pragma once
#include "sdk.h"

namespace SDK
{
	enum class RigidbodyConstraints : int32_t
	{
		None = 0,
		FreezePositionX = 2,
		FreezePositionY = 4,
		FreezePositionZ = 8,
		FreezePosition = 14,
		FreezeRotationX = 16,
		FreezeRotationY = 32,
		FreezeRotationZ = 64,
		FreezeRotation = 112,
		FreezeAll = 126
	};

	struct Rigidbody
	{
	};

	DEC_MET(Rigidbody_Set_IsKinematic, void(*)(Rigidbody* rigidbody, bool isKinematic, MethodInfo* methodInfo), "UnityEngine.PhysicsModule", "UnityEngine", "Rigidbody", "set_isKinematic", 1);
	DEC_MET(Rigidbody_Get_IsKinematic, bool(*)(Rigidbody* rigidbody, MethodInfo* methodInfo), "UnityEngine.PhysicsModule", "UnityEngine", "Rigidbody", "get_isKinematic", 0);
	DEC_MET(Rigidbody_Get_Constraints, RigidbodyConstraints(*)(Rigidbody* rigidbody, MethodInfo* methodInfo), "UnityEngine.PhysicsModule", "UnityEngine", "Rigidbody", "get_constraints", 0);
	DEC_MET(Rigidbody_Set_Constraints, void(*)(Rigidbody* rigidbody, RigidbodyConstraints constraints, MethodInfo* methodInfo), "UnityEngine.PhysicsModule", "UnityEngine", "Rigidbody", "set_constraints", 1);
	DEC_MET(Rigidbody_Set_Position, void(*)(Rigidbody* rigidbody, Vector3 position, MethodInfo* methodInfo), "UnityEngine.PhysicsModule", "UnityEngine", "Rigidbody", "set_position", 1);
}

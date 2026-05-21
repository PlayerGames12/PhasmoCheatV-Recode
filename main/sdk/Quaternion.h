#pragma once
#include "sdk.h"

namespace SDK
{
	struct Quaternion
	{
		float X;
		float Y;
		float Z;
		float W;
	};

	inline Quaternion identityQuaternion = { 0, 0, 0, 0 };

	DEC_MET(Quaternion_LookRotation, Quaternion(*)(Vector3 forward, Vector3 upwards, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Quaternion", "LookRotation", 2);
}

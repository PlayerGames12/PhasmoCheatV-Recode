#pragma once
#include "sdk.h"

namespace SDK
{
	struct Camera
	{
	};

	DEC_MET(Camera_WorldToScreenPoint, Vector3(*)(Camera* camera, Vector3 worldPoint, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Camera", "WorldToScreenPoint", 1);
	DEC_MET(Camera_Get_FieldOfView, float(*)(Camera* camera, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "Camera", "get_fieldOfView", 0);
	DEC_MET(Camera_Set_FieldOfView, void(*)(Camera* camera, float value, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "Camera", "set_fieldOfView", 1);
}

#pragma once
#include "sdk.h"

namespace SDK
{
	struct Component
	{
	};

	DEC_MET(Component_Get_Transform, Transform* (*)(Component* component, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Component", "get_transform", 0);
	DEC_MET(Component_Get_GameObject, GameObject* (*)(Component* component, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Component", "get_gameObject", 0);
}

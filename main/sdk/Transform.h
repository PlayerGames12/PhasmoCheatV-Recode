#pragma once
#include "sdk.h"

namespace SDK
{
    struct Transform
    {
    };

    DEC_MET(Transform_Get_Position, Vector3(*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_position", 0);
    DEC_MET(Transform_Set_Position, void(*)(Transform* transform, Vector3 position, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "set_position", 1);

    DEC_MET(Transform_Get_Right, Vector3(*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_right", 0);
    DEC_MET(Transform_Get_Up, Vector3(*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_up", 0);
    DEC_MET(Transform_Get_Forward, Vector3(*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_forward", 0);
    DEC_MET(Transform_Get_localScale, Vector3(*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_localScale", 0);

    DEC_MET(Transform_Get_Rotation, Quaternion(*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_rotation", 0);
    DEC_MET(Transform_Set_Rotation, void(*)(Transform* transform, Quaternion rotation, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "set_rotation", 1);

    DEC_MET(Transform_Get_Parent, Transform* (*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_parent", 0);
    DEC_MET(Transform_Set_Parent, void(*)(Transform* transform, Transform* parent, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "set_parent", 1);

    DEC_MET(Transform_get_childCount, int(*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_childCount", 0);
    DEC_MET(Transform_GetChild, Transform* (*)(Transform* transform, int32_t index, MethodInfo* MethodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "GetChild", 1);
    DEC_MET(Transform_IsChildOf, bool(*)(Transform* transform, Transform* parent, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "IsChildOf", 1);

    DEC_MET(Transform_SetSiblingIndex, void(*)(Transform* transform, int32_t index, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "SetSiblingIndex", 1);
    DEC_MET(Transform_GetSiblingIndex, int32_t(*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "GetSiblingIndex", 0);

	DEC_MET(Transform_Find, Transform* (*)(Transform* transform, SDK::String* name, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "Find", 1);
}

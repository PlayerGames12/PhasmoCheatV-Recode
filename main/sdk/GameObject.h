#pragma once
#include "sdk.h"

namespace SDK
{
    struct Component;
    struct GameObject;

    struct GameObjectArray
    {
        void* Clazz;
        void* Monitor;
        void* Bounds;
        uint32_t MaxLength;
        GameObject* Vector[1];
    };

    DEC_MET(GameObject_get_transform, Transform* (*)(GameObject* gameObject, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "get_transform", 0);
    DEC_MET(GameObject_FindGameObjectsWithTag, GameObjectArray* (*)(String* tag, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "FindGameObjectsWithTag", 1);
    DEC_MET(GameObject_Set_Layer, void* (*)(GameObject* gameObject, int layer, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "set_layer", 1);
    DEC_MET(GameObject_Get_Layer, int32_t(*)(GameObject* gameObject, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "get_layer", 0);
    DEC_MET(GameObject_SetActive, void(*)(GameObject* gameObject, bool value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "SetActive", 1);
    DEC_MET(GameObject_get_activeSelf, bool(*)(GameObject* gameObject, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "get_activeSelf", 0);
    DEC_MET(GameObject_AddComponent, SDK::Component* (*)(SDK::GameObject* gameObject, SDK::Type* componentType, SDK::MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "AddComponent", 1);
    DEC_MET(GameObject_GetComponent, SDK::Component* (*)(SDK::GameObject* gameObject, SDK::Type* componentType, SDK::MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponent", 1);
    DEC_MET(GameObject_GetComponentByName, SDK::Component* (*)(SDK::GameObject* gameObject, SDK::String* type, SDK::MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponentByName", 1);
    DEC_MET(GameObject_Find, SDK::GameObject* (*)(SDK::String* name, SDK::MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "Find", 1);
    DEC_MET(GameObject_set_tag, void(*)(GameObject* gameObject, String* tag, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "set_tag", 1);
    DEC_MET(GameObject_get_tag, String* (*)(GameObject* gameObject, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "get_tag", 0);

    DECLARE_FUNCTION_POINTER(GameObject_Find_RVA, SDK::GameObject* (*)(SDK::String* name, SDK::MethodInfo* method), 0x5072650);
}

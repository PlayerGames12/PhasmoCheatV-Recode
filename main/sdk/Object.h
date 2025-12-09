#pragma once
#include "sdk.h"

namespace SDK
{
    struct Object
    {
        void* Clazz;
        void* Monitor;
        void* Fields;
    };

    struct ObjectArray
    {
        void* Clazz;
        void* Monitor;
        void* Bounds;
        void* MaxLength;
        Object* Vector[65535];
    };

    struct __declspec(align(8)) ListObjectFields
    {
        ObjectArray* Items;
        int32_t Size;
        int32_t Version;
        void* SyncRoot;
    };

    struct ListObject
    {
        void* Clazz;
        void* Monitor;
        ListObjectFields Fields;
    };

    DEC_MET(Object_Get_Name, SDK::String* (*)(Object* object, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Object", "get_name", 0);
    DEC_MET(Object_Destroy, void (*)(SDK::Object* object, SDK::MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Object", "Destroy", 1);
    DEC_MET(Object_FindObjectsOfType, ObjectArray* (*)(Type* type, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Object", "FindObjectsOfType", 1);

}
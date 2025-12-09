#pragma once
#include "sdk.h"

namespace SDK 
{
    struct TypeFields
    {
        void* _impl;
    };

    struct Type
    {
        void* klass;
        void* monitor;
        TypeFields Fields;
    };

	DEC_MET(System_Type_GetType, SDK::Type* (*)(String* typeName, SDK::MethodInfo* method), "mscorlib", "System", "Type", "GetType", 1);
}
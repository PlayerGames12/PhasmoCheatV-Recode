#pragma once
#include "sdk.h"

namespace SDK
{
    struct ScriptableRenderContext
    {
        void* m_Ptr;
    };

    DEC_MET(ScriptableRenderContext_Submit, void(*)(ScriptableRenderContext* scriptableRenderContext, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine.Rendering", "ScriptableRenderContext", "Submit", 0);
}
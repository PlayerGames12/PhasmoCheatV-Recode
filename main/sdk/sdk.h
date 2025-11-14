#pragma once
#include "il2cpp/il2cpp.h"
#include "../main/logging/logger.h" // For LOGS

using namespace PhasmoCheatV;

// EXPAMPLE USE: DEC_MET(Behaviour_Set_Enabled, void(*)(Behaviour* behaviour, bool enabled, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Behaviour", "set_enabled", 1);
#define DEC_MET(NAME, TYPE, ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT) \
using NAME##_ptr = TYPE; \
inline NAME##_ptr NAME = reinterpret_cast<NAME##_ptr>(il2cpp_get_method_pointer(ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT));

namespace SDK
{
    inline bool Initialize()
    {
		LOG_INFO("Initializing IL2CPP SDK...");
		LOG_INFO("GameAssembly.dll base address: ", (GetModuleHandleA("GameAssembly.dll")));
        return il2cpp_initialize();
    }
}

#include "MethodInfo.h"
#include "Vector2.h"
#include "Vector3.h"
#include "String.h"
#include "MonoBehaviour.h"
#include "Cursor.h"
#include "GhostEvidence.h"
#include "GhostTraits.h"
#include "GhostInfo.h"
#include "GhostAI.h"
#include "ExitLevel.h"
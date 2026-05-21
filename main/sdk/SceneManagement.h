#pragma once
#include "sdk.h"

namespace SDK
{
	struct SceneManagement;

    DEC_MET(SceneManagement_Internal_SceneLoaded, void(*)(void* scene, int32_t mode, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine.SceneManagement","SceneManager", "Internal_SceneLoaded", 2);
}
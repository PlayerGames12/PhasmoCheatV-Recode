#pragma once
#include "sdk.h"

namespace SDK
{
	struct Scene
	{
		int m_Handle;
	};

	DEC_MET(SceneManager_GetActiveScene, Scene(*)(MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine.SceneManagement", "SceneManager", "GetActiveScene", 0);
	DEC_MET(Scene_get_name, String* (*)(Scene* scene, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine.SceneManagement", "Scene", "get_name", 0);
}

#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkSceneManagement_Internal_SceneLoaded(void* scene, int32_t mode, SDK::MethodInfo* method)
{
	LOG_CALL("Called SceneManagement_Internal_SceneLoaded");

	if (CheatWork)
	{
		InGame::g_GameObjectCache.clear();
		InGame::FBGO = nullptr;
	}

	SDK::SceneManagement_Internal_SceneLoaded(scene, mode, method);
}
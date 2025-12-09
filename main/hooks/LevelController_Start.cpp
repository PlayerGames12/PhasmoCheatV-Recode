#include "../Includes.h"
#include "hooking.h"

using namespace PhasmoCheatV;

void Hooks::hkLevelController_Start(SDK::LevelController* levelController, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called LevelController_Start");
	SDK::LevelController_Start(levelController, methodInfo);

	if (CheatWork) {
		InGame::levelController = levelController;
		InGame::fuseBox = levelController->Fields.fuseBox;
	}
}

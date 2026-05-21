#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkGameController_Awake(SDK::GameController* gameController, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called GameController_Awake");

	if (CheatWork)
		InGame::gameController = gameController;

	SDK::GameController_Awake(gameController, methodInfo);
}
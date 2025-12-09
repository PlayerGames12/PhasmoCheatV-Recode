#include "../Includes.h"
#include "hooking.h"

using namespace PhasmoCheatV;

void Hooks::hkPauseMenuController_Leave(SDK::PauseMenuController* pauseMenuController, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called PauseMenuController_Leave");
	if (CheatWork)
		InGame::Reset();
	LOG_DEBUG("In-game pointers reset on pause menu leave");
	SDK::PauseMenuController_Leave(pauseMenuController, methodInfo);
}
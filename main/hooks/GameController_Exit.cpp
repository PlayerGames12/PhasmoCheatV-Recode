#include "../Includes.h"
#include "hooking.h"

using namespace PhasmoCheatV;

void Hooks::hkGameController_Exit(SDK::GameController* gameController, void* photon, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called GameController_Exit");
	if (CheatWork)
		InGame::Reset();
	LOG_DEBUG("In-game pointers reset on game controller exit");
	SDK::GameController_Exit(gameController, photon, methodInfo);
}

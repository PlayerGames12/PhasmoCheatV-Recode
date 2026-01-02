#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkLightningController_Start(SDK::LightningController* lightningController, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called LightningController_Start");

	if (CheatWork)
		InGame::lightningController = lightningController;

	SDK::LightningController_Start(lightningController, methodInfo);
}
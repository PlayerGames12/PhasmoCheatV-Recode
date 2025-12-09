#include "../Includes.h"
#include "hooking.h"

using namespace PhasmoCheatV;

void Hooks::hkMapController_Start(SDK::MapController* mapController, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called MapController_Start");
	if (CheatWork)
		InGame::mapController = mapController;
	SDK::MapController_Start(mapController, methodInfo);
}

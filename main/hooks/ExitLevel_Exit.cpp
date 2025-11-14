#include "../Includes.h"
#include "hooking.h"

using namespace PhasmoCheatV;

void Hooks::hkExitLevel_Exit(SDK::ExitLevel* exitLevel, void* photon, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called ExitLevel_Exit");
	InGame::Reset();
	LOG_DEBUG("In-game pointers reset on level exit");
	SDK::ExitLevel_Exit(exitLevel, photon, methodInfo);
}

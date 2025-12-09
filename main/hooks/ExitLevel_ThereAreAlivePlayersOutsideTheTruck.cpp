#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

bool Hooks::hkExitLevel_ThereAreAlivePlayersOutsideTheTruck(SDK::ExitLevel* exitLevel, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called ExitLevel_ThereAreAlivePlayersOutsideTheTruck");

	return CALL_METHOD_ARGS(Misc, ExitVanOne, ExitVanOneMain, exitLevel, methodInfo);
}
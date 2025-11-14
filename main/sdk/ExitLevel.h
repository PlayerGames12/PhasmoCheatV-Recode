#pragma once
#include "sdk.h"

namespace SDK
{
	struct ExitLevel;

	DEC_MET(ExitLevel_Exit, void(*)(ExitLevel* exitLevel, void* photonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "ExitLevel", "Exit", 1);
	DEC_MET(ExitLevel_ThereAreAlivePlayersOutsideTheTruck, bool(*)(ExitLevel* exitLevel, MethodInfo* methodInfo), "Assembly-CSharp", "", "ExitLevel", "ThereAreAlivePlayersOutsideTheTruck", 0);
}

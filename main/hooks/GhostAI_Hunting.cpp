#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkGhostAI_Hunting(SDK::GhostAI* ghostAI, bool isHunting, int obakeArrayID, void* photon, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called GhostAI_Hunting");
	if (CheatWork)
		Globals::isHunting = isHunting;
	SDK::GhostAI_Hunting(ghostAI, isHunting, obakeArrayID, photon, methodInfo);
}
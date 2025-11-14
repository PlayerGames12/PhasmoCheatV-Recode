#include "../Includes.h"
#include "hooking.h"

using namespace PhasmoCheatV;

void Hooks::hkGhostAI_Start(SDK::GhostAI* ghostAI, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called GhostAI_Start");
	SDK::GhostAI_Start(ghostAI, methodInfo);

	if (CheatWork) {
		InGame::ghostAI = ghostAI;
	}
}

#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkGhostAI_Hunting(SDK::GhostAI* ghostAI, bool isHunting, int obakeArrayID, void* photon, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called GhostAI_Hunting");
	if (CheatWork)
	{
		CALL_METHOD_ARGS(Visuals, NotifyInfo, RenderNotifyHunt, ghostAI, isHunting);
		Globals::isHunting = isHunting;
	}
	SDK::GhostAI_Hunting(ghostAI, isHunting, obakeArrayID, photon, methodInfo);
}
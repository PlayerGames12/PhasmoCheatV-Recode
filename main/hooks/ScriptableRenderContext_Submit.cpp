#include "../Includes.h"
#include "../discordrpc/discordrpc.h"

using namespace PhasmoCheatV;

void Hooks::hkScriptableRenderContext_Submit(SDK::ScriptableRenderContext* context, SDK::MethodInfo* methodInfo)
{
	LOG_CALL_UPDATE("Called ScriptableRenderContext_Submit");

	if (CheatWork)
		Discord::DiscordRPCStatusHandler();

	SDK::ScriptableRenderContext_Submit(context, methodInfo);
}
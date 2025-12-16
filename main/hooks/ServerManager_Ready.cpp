#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkServerManager_Ready(SDK::ServerManager* serverManager, bool on, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called ServerManager_Ready");

	SDK::ServerManager_Ready(serverManager, on, methodInfo);

	CALL_METHOD_ARGS(Misc, ForceStart, ForceStartMain, serverManager);
}
#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkServerManager_KickPlayerNetworked(SDK::ServerManager* serverManager, bool isBanned, void* photon, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called ServerManager_KickPlayerNetworked");

	CALL_METHOD_IF_ACTIVE_ARGS(Misc, AntiKick, AntiKickMain, serverManager, isBanned, photon, methodInfo);
}
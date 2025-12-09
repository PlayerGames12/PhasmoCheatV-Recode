#include "../Includes.h"
#include "../features/feats/godmode/godmode.h"

using namespace PhasmoCheatV;

std::nullptr_t Hooks::hkPlayer_StartKillingPlayerNetworked(SDK::Player* player, bool b1, void* photon, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called Player_StartKillingPlayerNetworked");
	
	if (GET_ACTIVE(Players, GodMode) && player == Utils::GetLocalPlayer()) return nullptr;

	return SDK::Player_StartKillingPlayerNetworked(player, b1, photon, methodInfo);
}
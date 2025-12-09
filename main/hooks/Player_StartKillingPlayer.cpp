#include "../Includes.h"
#include "../features/feats/godmode/godmode.h"

using namespace PhasmoCheatV;

void Hooks::hkPlayer_StartKillingPlayer(SDK::Player* player, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called Player_StartKillingPlayer");

	if (GET_ACTIVE(Players, GodMode) && player == Utils::GetLocalPlayer()) return;

	SDK::Player_StartKillingPlayer(player, methodInfo);
}
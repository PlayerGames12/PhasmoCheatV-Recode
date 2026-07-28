#include "../Includes.h"
#include "../main/features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkPlayer_NotifyOfDeathEnd(SDK::Player* player, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called Player_NotifyOfDeathEnd");

	//if (CheatWork && Utils::GetLocalPlayer() == player)
		//CALL_METHOD(Movement, Teleport, TeleportToTruck);

	SDK::Player_NotifyOfDeathEnd(player, methodInfo);
}
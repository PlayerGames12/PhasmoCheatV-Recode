#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkPlayer_NotifyOfDeathStart(SDK::Player* player, void* photonMessageInfo, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called Player_NotifyOfDeathStart");

	//SDK::Vector3 vec3 = { 789, 50, 789 };

	//if (CheatWork && Utils::GetLocalPlayer() == player)
		//Utils::TpPlayerToVec3(player, vec3);

	SDK::Player_NotifyOfDeathStart(player, photonMessageInfo, methodInfo);
}
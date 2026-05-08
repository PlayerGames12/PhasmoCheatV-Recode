#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

std::nullptr_t Hooks::hkPlayer_StartDeathAnimation(SDK::Player* player, int32_t a1, bool a2, void* photon, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called Player_StartDeathAnimation");

	if (GET_ACTIVE(Players, GodMode) && player == Utils::GetLocalPlayer())
		return nullptr;

	return SDK::Player_StartDeathAnimation(player, a1, a2, photon, methodInfo);
} 
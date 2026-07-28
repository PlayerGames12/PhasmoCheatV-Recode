#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkPlayerStamina_Update(SDK::PlayerStamina* playerStamina, SDK::MethodInfo* methodInfo)
{
	LOG_CALL_UPDATE("Called PlayerStamina_Update");

	CALL_METHOD_IF_ACTIVE_ARGS(Movement, InfinityStamina, InfinityStaminaMain, playerStamina);

	SDK::PlayerStamina_Update(playerStamina, methodInfo);
}
#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkPlayerStamina_Update(SDK::PlayerStamina* playerStamina, SDK::MethodInfo* methodInfo)
{
	LOG_CALL_UPDATE("Called PlayerStamina_Update");

	if (CheatWork &&
		!InGame::playerStamina ||
		SDK::Object_IsNativeAlive(reinterpret_cast<SDK::Object*>(
			SDK::Component_Get_GameObject(
				reinterpret_cast<SDK::Component*>(InGame::playerStamina), nullptr)),
			nullptr))
	{
		InGame::playerStamina = playerStamina;
	}

	CALL_METHOD_IF_ACTIVE_ARGS(Movement, InfinityStamina, InfinityStaminaMain, playerStamina);

	SDK::PlayerStamina_Update(playerStamina, methodInfo);
}
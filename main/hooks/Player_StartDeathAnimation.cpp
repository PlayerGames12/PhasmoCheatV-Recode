#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

std::string DeathType2Str(SDK::deathType type)
{
	switch (type)
	{
	case SDK::deathType::HangedMan:
		return "Hanged man (tarot card)";
	case SDK::deathType::SnappedNeck:
		return "Snapped neck (ghost)";
	default:
		return "Unknown";
	}
}

void Hooks::hkPlayer_BeginDeathSequence(SDK::Player* player, SDK::deathType deadType, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called Player_BeginDeathSequence");

	if (GET_ACTIVE(Players, GodMode) && player == Utils::GetLocalPlayer())
	{
		if (GET_ACTIVE(Visuals, NotifyInfo)) NOTIFY_INFO_QUICK(LANG("PlayerDeath_GodModePrevented") + DeathType2Str(deadType));
		return;
	}

	SDK::Player_BeginDeathSequence(player, deadType, methodInfo);
}
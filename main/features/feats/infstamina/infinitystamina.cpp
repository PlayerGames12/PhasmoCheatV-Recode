#include "infinitystamina.h"

using namespace PhasmoCheatV::Features::Movement;

InfinityStamina::InfinityStamina() : FeatureCore(LANG("InfinityStamina_Header"), TYPE_MOVEMENT) {}

void InfinityStamina::OnMenuRender()
{
	bool enabled = IsActive();
	if (BCheckBox(LANG("InfinityStaminaEnable"), &enabled, "b_InfinityStaminaEnable"))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
}

void InfinityStamina::InfinityStaminaMain(SDK::PlayerStamina* playerStamina)
{
	if (IsActive() && playerStamina->Fields.CurrentStamina <= 1.f)
		playerStamina->Fields.CurrentStamina = 3.f;
}

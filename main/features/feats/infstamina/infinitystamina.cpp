#include "infinitystamina.h"

using namespace PhasmoCheatV::Features::Movement;

InfinityStamina::InfinityStamina() : FeatureCore("Infinity Stamina", TYPE_MOVEMENT) {}

void InfinityStamina::OnMenuRender()
{
	bool enabled = IsActive();
	if (ImGui::Checkbox("Infinity Stamina", &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
}

void InfinityStamina::InfinityStaminaMain(SDK::PlayerStamina* playerStamina)
{
	if (IsActive() && playerStamina->Fields.CurrentStamina != 3.f)
		playerStamina->Fields.CurrentStamina = 3.f;
}

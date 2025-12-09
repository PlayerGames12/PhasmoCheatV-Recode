#include "customspeed.h"

using namespace PhasmoCheatV::Features::Movement;

CustomSpeed::CustomSpeed() : FeatureCore("Custom Speed", TYPE_MOVEMENT)
{
	DECLARE_CONFIG(GetConfigManager(), "Speed", float, 1.6f);
}

void CustomSpeed::OnMenuRender()
{
	bool enabled = IsActive();
	float custSpeed = CONFIG_FLOAT(GetConfigManager(), "Speed");
	if (ImGui::Checkbox("Enabled##custSpeed", &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
	if (ImGui::SliderFloat("Custom speed##custSpeed", &custSpeed, 0.f, 20.f, "%.1f"))
		SET_CONFIG_VALUE(GetConfigManager(), "Speed", float, custSpeed);
}

void CustomSpeed::CustomSpeedMain(SDK::FirstPersonController* firstPersonController)
{
	if (IsActive())
	{
		firstPersonController->Fields.CurrentSpeed = CONFIG_FLOAT(GetConfigManager(), "Speed");
	}
	else
	{
		firstPersonController->Fields.CurrentSpeed = !firstPersonController->Fields.IsSprinting ? 1.6f : 3.f;
	}
}
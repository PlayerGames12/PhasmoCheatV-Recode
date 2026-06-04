#include "customspeed.h"

using namespace PhasmoCheatV::Features::Movement;

CustomSpeed::CustomSpeed() : FeatureCore(LANG("CustomSpeed_Header"), TYPE_MOVEMENT)
{
	DECLARE_CONFIG(GetConfigManager(), "Speed", float, 1.6f);
	DECLARE_CONFIG(GetConfigManager(), "SprintSpeed", float, 3.f);
}

void CustomSpeed::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

	bool enabled = IsActive();
	float custSpeed = CONFIG_FLOAT(GetConfigManager(), "Speed");
	float custSprintSpeed = CONFIG_FLOAT(GetConfigManager(), "SprintSpeed");
	if (BCheckBox(LANG("CustomSpeedEnabled"), &enabled, "b_CustomSpeedEnabled"))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}

	if (!enabled)
	{
		ImGui::PopStyleVar();
		return;
	}

	if (ImGui::SliderFloat(LANG("CustomSpeedSlider"), &custSpeed, 0.f, 20.f, "%.1f"))
		SET_CONFIG_VALUE(GetConfigManager(), "Speed", float, custSpeed);
	if (ImGui::SliderFloat(LANG("CustomSprintSpeedSlider"), &custSprintSpeed, 0.f, 20.f, "%.1f"))
		SET_CONFIG_VALUE(GetConfigManager(), "SprintSpeed", float, custSprintSpeed);

	ImGui::PopStyleVar();
}

void CustomSpeed::CustomSpeedMain(SDK::FirstPersonController* firstPersonController)
{
	if (IsActive())
	{
		firstPersonController->Fields.CurrentSpeed = !firstPersonController->Fields.IsSprinting ? 
			CONFIG_FLOAT(GetConfigManager(), "Speed") : 
			CONFIG_FLOAT(GetConfigManager(), "SprintSpeed");
		active = true;
	}
	else
	{
		if (active)
			firstPersonController->Fields.CurrentSpeed = !firstPersonController->Fields.IsSprinting ? 1.6f : 3.f;
		active = false;
	}
}
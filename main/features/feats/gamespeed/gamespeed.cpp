#include "gamespeed.h"

using namespace PhasmoCheatV::Features::Misc;

GameSpeed::GameSpeed() : FeatureCore(LANG("GameSpeed_Header"), TYPE_MISC)
{
	DECLARE_CONFIG(GetConfigManager(), "Speed", float, 1.0f);
}

void GameSpeed::OnActivate()
{
	SDK::Time_Set_TimeScale(CONFIG_FLOAT(GetConfigManager(), "Speed"), nullptr);
}

void GameSpeed::OnDeactivate()
{
	SDK::Time_Set_TimeScale(1.0f, nullptr);
}

void GameSpeed::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

	bool enabled = IsActive();
	if (BCheckBox(LANG("GameSpeedEnabled"), &enabled, "b_GameSpeedEnabled"))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}

	if (enabled)
	{
		float speed = CONFIG_FLOAT(GetConfigManager(), "Speed");
		if (ImGui::SliderFloat(LANG("GameSpeedSlider"), &speed, 0.0f, 10.0f, "%.1f"))
		{
			SET_CONFIG_VALUE(GetConfigManager(), "Speed", float, speed);
			if (IsActive())
				SDK::Time_Set_TimeScale(speed, nullptr);
		}
	}

	ImGui::PopStyleVar();
}

void GameSpeed::GameSpeedMain()
{
	if (IsActive())
		SDK::Time_Set_TimeScale(CONFIG_FLOAT(GetConfigManager(), "Speed"), nullptr);
}

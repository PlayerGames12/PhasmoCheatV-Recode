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
	bool enabled = IsActive();
	float speed = CONFIG_FLOAT(GetConfigManager(), "Speed");
	if (BCheckBox(LANG("GameSpeedEnabled"), &enabled, "b_GameSpeedEnabled"))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
	if (ImGui::SliderFloat(LANG("GameSpeedSlider"), &speed, 0.0f, 10.0f, "%.1f"))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Speed", float, speed);
		if (IsActive())
			SDK::Time_Set_TimeScale(speed, nullptr);
	}
}

void GameSpeed::GameSpeedMain()
{
	if (IsActive())
		SDK::Time_Set_TimeScale(CONFIG_FLOAT(GetConfigManager(), "Speed"), nullptr);
}

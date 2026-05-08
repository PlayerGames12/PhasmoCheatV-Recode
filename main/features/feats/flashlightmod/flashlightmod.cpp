#include "flashlightmod.h"

using namespace PhasmoCheatV::Features::Misc;

FlashLightModifier::FlashLightModifier() : FeatureCore(LANG("FlashlightModifier_Header"), TYPE_MISC) 
{
	DECLARE_CONFIG(GetConfigManager(), "NoFlicker", bool, false);
	DECLARE_CONFIG(GetConfigManager(), "DisableDifficultyCheck", bool, false);
}

void FlashLightModifier::OnDeactivate()
{
	SDK::Jnz_if_flashlights_restore();
	SDK::Jnz_if_isNearActiveGhost_restore();
}

void FlashLightModifier::OnActivate()
{
	bool noFlicker = CONFIG_BOOL(GetConfigManager(), "NoFlicker");
	bool disableDifficultyCheck = CONFIG_BOOL(GetConfigManager(), "DisableDifficultyCheck");

	if (noFlicker)
		SDK::Jnz_if_isNearActiveGhost_nop(2);
	if (disableDifficultyCheck)
		SDK::Jnz_if_flashlights_edit({ 0xEB }, 0);
}

void FlashLightModifier::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));
	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("FlashlightModifierEnable"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}

	if (enabled)
	{
		bool noFlicker = CONFIG_BOOL(GetConfigManager(), "NoFlicker");
		bool disableDifficultyCheck = CONFIG_BOOL(GetConfigManager(), "DisableDifficultyCheck");

		if (ImGui::Checkbox(LANG("NoFlashlightFlicker"), &noFlicker))
		{
			SET_CONFIG_VALUE(GetConfigManager(), "NoFlicker", bool, noFlicker);
			noFlicker ? SDK::Jnz_if_isNearActiveGhost_nop(2) : SDK::Jnz_if_isNearActiveGhost_restore();
		}

		if (ImGui::Checkbox(LANG("DisableDifficultyCheck"), &disableDifficultyCheck))
		{
			SET_CONFIG_VALUE(GetConfigManager(), "DisableDifficultyCheck", bool, disableDifficultyCheck);
			disableDifficultyCheck ? SDK::Jnz_if_flashlights_edit({ 0xEB }, 0) : SDK::Jnz_if_flashlights_restore();
		}
	}
	ImGui::PopStyleVar();
}
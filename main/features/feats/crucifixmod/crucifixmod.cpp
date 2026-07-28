#include "crucifixmod.h"

using namespace PhasmoCheatV::Features::Misc;

CrucifixModifier::CrucifixModifier() : FeatureCore(LANG("CrucifixModifier_Header"), TYPE_MISC)
{
	DECLARE_CONFIG(GetConfigManager(), "ECustomRange", bool, false);
	DECLARE_CONFIG(GetConfigManager(), "CustomRange", float, 5.f);
	DECLARE_CONFIG(GetConfigManager(), "InfiniteUses", bool, false);
}

void CrucifixModifier::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("EnableCrucifixModifier"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		enabled ? OnActivate() : OnDeactivate();
	}
	
	if (!enabled)
	{
		ImGui::PopStyleVar();
		return;
	}

	auto DrawConfigCheckbox = [&](const char* langKey, const char* configKey) {
		bool val = CONFIG_BOOL(GetConfigManager(), configKey);
		if (ImGui::Checkbox(LANG(langKey), &val))
			SET_CONFIG_VALUE(GetConfigManager(), configKey, bool, val);
		};

	DrawConfigCheckbox("EnableCustomRange", "ECustomRange");
	
	ImGui::SameLine();
	
	float customRange = CONFIG_FLOAT(GetConfigManager(), "CustomRange");
	if (ImGui::SliderFloat(LANG("CystomRange"), &customRange, .1f, 100.f, "%.1f"))
		SET_CONFIG_VALUE(GetConfigManager(), "CustomRange", float, customRange);

	DrawConfigCheckbox("EnableInfiniteUses", "InfiniteUses");

	ImGui::PopStyleVar();
}

void CrucifixModifier::CrucifixModifierHook(SDK::Crucifix* crucifix)
{
	if (!IsActive() || !crucifix || !SDK::PhotonNetwork_Get_IsMasterClient(nullptr))
		return;

	bool ecustomRange = CONFIG_BOOL(GetConfigManager(), "ECustomRange");
	bool infiniteUses = CONFIG_BOOL(GetConfigManager(), "InfiniteUses");
	float customRange = CONFIG_FLOAT(GetConfigManager(), "CustomRange");

	if (ecustomRange)
		crucifix->Fields.range = 789.f;

	if (infiniteUses)
		crucifix->Fields.useCount = 2;
}
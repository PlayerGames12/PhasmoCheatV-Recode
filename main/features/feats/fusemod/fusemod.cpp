#include "fusemod.h"

using namespace PhasmoCheatV::Features::Map;

FuseBoxModifier::FuseBoxModifier() : FeatureCore(LANG("FuseBoxModifier_Header"), TYPE_MAP) 
{
	DECLARE_CONFIG(GetConfigManager(), "AutoOn", bool, false);
}

void FuseBoxModifier::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("EnableFuseBoxModifier"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		enabled ? OnActivate() : OnDeactivate();
	}

	if (!enabled)
	{
		ImGui::PopStyleVar();
		return;
	}

	bool AutoOn = CONFIG_BOOL(GetConfigManager(), "AutoOn");
	if (ImGui::Checkbox(LANG("AutoOnFuse"), &AutoOn))
		SET_CONFIG_VALUE(GetConfigManager(), "AutoOn", bool, AutoOn);

	ImGui::PopStyleVar();
}

void FuseBoxModifier::FuseBoxModifierHandler()
{
	auto* levelController = InGame::levelController;
	if (!levelController)
		return;
	auto* fuseBox = levelController->Fields.fuseBox;
	if (!fuseBox)
		return;

	bool fuseOn = fuseBox->Fields.IsOn;

	// configs
	bool active = IsActive();
	bool AutoOn = CONFIG_BOOL(GetConfigManager(), "AutoOn");

	if (!active)
		return;
	
	if (AutoOn && !fuseOn)
	{
		SDK::FuseBox_Use(fuseBox, nullptr);
		NOTIFY_INFO_QUICK(LANG("FuseBoxOnByCheat"));
	}
}
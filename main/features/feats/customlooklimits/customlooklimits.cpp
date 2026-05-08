#include "customlooklimits.h"

using namespace PhasmoCheatV::Features::Players;

CustomLookLimits::CustomLookLimits() : FeatureCore(LANG("CustomLookLimits_Header"), TYPE_PLAYERS)
{
	DECLARE_CONFIG(GetConfigManager(), "NoLimits", bool, false);
	DECLARE_CONFIG(GetConfigManager(), "MinX", float, -90.f);
	DECLARE_CONFIG(GetConfigManager(), "MaxX", float, 90.f);
}

void CustomLookLimits::OnMenuRender()
{
	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("LookLimitsEnable"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}

	if (enabled)
	{
		bool noLimits = CONFIG_BOOL(GetConfigManager(), "NoLimits");
		if (ImGui::Checkbox(LANG("NoLimits"), &noLimits))
		{
			SET_CONFIG_VALUE(GetConfigManager(), "NoLimits", bool, noLimits);
		}

		if (!noLimits)
		{
			float minX = CONFIG_FLOAT(GetConfigManager(), "MinX");
			float maxX = CONFIG_FLOAT(GetConfigManager(), "MaxX");

			if (ImGui::SliderFloat(LANG("MinX"), &minX, -360.f, 360.f))
				SET_CONFIG_VALUE(GetConfigManager(), "MinX", float, minX);
			if (ImGui::SliderFloat(LANG("MaxX"), &maxX, -360.f, 360.f))
				SET_CONFIG_VALUE(GetConfigManager(), "MaxX", float, maxX);
		}
	}
}

void CustomLookLimits::OnDeactivate()
{
	auto localPlayer = Utils::GetLocalPlayer();
	if (!localPlayer)
		return;

	auto firstPersonController = InGame::firstPersonController;
	if (!firstPersonController)
		return;

	auto mouseLook = firstPersonController->Fields.MouseLook;
	if (!mouseLook)
		return;

	mouseLook->Fields.MinimumX = -90.f;
	mouseLook->Fields.MaximumX = 90.f;
}

void CustomLookLimits::CustomLookLimitsMain(SDK::FirstPersonController* firstPersonController)
{
	if (!IsActive())
		return;

	auto mouseLook = firstPersonController->Fields.MouseLook;
	if (!mouseLook)
		return;

	bool noLimits = CONFIG_BOOL(GetConfigManager(), "NoLimits");
	if (noLimits)
	{
		mouseLook->Fields.MinimumX = -360.f;
		mouseLook->Fields.MaximumX = 360.f;
	}
	else
	{
		mouseLook->Fields.MinimumX = GetConfigManager()->GetConfigValue<float>("MinX");
		mouseLook->Fields.MaximumX = GetConfigManager()->GetConfigValue<float>("MaxX");
	}
}

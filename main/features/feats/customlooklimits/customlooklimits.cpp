#include "customlooklimits.h"

using namespace PhasmoCheatV::Features::Players;

CustomLookLimits::CustomLookLimits() : FeatureCore("Custom Look Limits", TYPE_PLAYERS)
{
	DECLARE_CONFIG(GetConfigManager(), "NoLimits", bool, false);
	DECLARE_CONFIG(GetConfigManager(), "MinX", float, -90.f);
	DECLARE_CONFIG(GetConfigManager(), "MaxX", float, 90.f);
}

void CustomLookLimits::OnMenuRender()
{
	bool enabled = IsActive();
	if (ImGui::Checkbox("Enable Custom Look Limits", &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}

	if (enabled)
	{
		bool noLimits = CONFIG_BOOL(GetConfigManager(), "NoLimits");
		if (ImGui::Checkbox("No Limits", &noLimits))
		{
			SET_CONFIG_VALUE(GetConfigManager(), "NoLimits", bool, noLimits);
		}

		if (!noLimits)
		{
			float minX = CONFIG_FLOAT(GetConfigManager(), "MinX");
			float maxX = CONFIG_FLOAT(GetConfigManager(), "MaxX");

			if (ImGui::SliderFloat("Min X", &minX, -360.f, 360.f))
				SET_CONFIG_VALUE(GetConfigManager(), "MinX", float, minX);
			if (ImGui::SliderFloat("Max X", &maxX, -360.f, 360.f))
				SET_CONFIG_VALUE(GetConfigManager(), "MaxX", float, maxX);
		}
	}
}

void CustomLookLimits::OnDeactivate()
{
	auto localPlayer = Utils::GetLocalPlayer();
	if (!localPlayer)
		return;

	auto firstPersonController = localPlayer->Fields.FirstPersonController;
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

#include "pickup.h"

using namespace PhasmoCheatV::Features::Players;

Pickup::Pickup() : FeatureCore("Pickup", TYPE_PLAYERS)
{
	DECLARE_CONFIG(GetConfigManager(), "CustomThrow", float, 3.f);
	DECLARE_CONFIG(GetConfigManager(), "ThrowMultiplier", bool, false);
	DECLARE_CONFIG(GetConfigManager(), "CustomGrabDistance", float, 3.f);
	DECLARE_CONFIG(GetConfigManager(), "GrabDistanceMultiplier", bool, false);
}

void Pickup::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

	bool enabled = IsActive();

	if (ImGui::Checkbox("Enable Pickup", &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}

	if (enabled)
	{
		float CustomThrow = CONFIG_FLOAT(GetConfigManager(), "CustomThrow");
		bool ThrowMultiplier = CONFIG_BOOL(GetConfigManager(), "ThrowMultiplier");
		float CustomGrabDistance = CONFIG_FLOAT(GetConfigManager(), "CustomGrabDistance");
		bool GrabDistanceMultiplier = CONFIG_BOOL(GetConfigManager(), "GrabDistanceMultiplier");

		if (ImGui::Checkbox("Custom throw", &ThrowMultiplier))
			SET_CONFIG_VALUE(GetConfigManager(), "ThrowMultiplier", bool, ThrowMultiplier);
		if (ImGui::SliderFloat("Throw multiplier", &CustomThrow, 1.f, 100.0f, "%.1fx"))
			SET_CONFIG_VALUE(GetConfigManager(), "CustomThrow", float, CustomThrow);

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		if (ImGui::Checkbox("Custom grab distance", &GrabDistanceMultiplier))
			SET_CONFIG_VALUE(GetConfigManager(), "GrabDistanceMultiplier", bool, GrabDistanceMultiplier);
		if (ImGui::SliderFloat("Grab distance", &CustomGrabDistance, 1.f, 50.0f, "%.1f units"))
			SET_CONFIG_VALUE(GetConfigManager(), "CustomGrabDistance", float, CustomGrabDistance);
	}

	ImGui::PopStyleVar();
}

void Pickup::PickupMain()
{
	if (InGame::photonInstances.empty()) return;
	if (!IsActive()) return;
	if (CONFIG_BOOL(GetConfigManager(), "GrabDistanceMultiplier"))
	{
		float grabDistance = CONFIG_FLOAT(GetConfigManager(), "CustomGrabDistance");
		SDK::PCPropGrab_GrabDistance_wr(grabDistance);
	}
	for (auto* obj : InGame::photonInstances)
	{
		if (!obj) return;

		obj->Fields.isProp = true;
		obj->Fields.isItem = true;
		obj->Fields.isDroppable = true;
		obj->Fields.isUsable = true;

		if (CONFIG_BOOL(GetConfigManager(), "ThrowMultiplier"))
		{
			obj->Fields.throwMultiplier = CONFIG_FLOAT(GetConfigManager(), "CustomThrow");
		}
	}
}
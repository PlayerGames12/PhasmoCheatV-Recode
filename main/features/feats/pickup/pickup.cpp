#include "pickup.h"

using namespace PhasmoCheatV::Features::Players;

Pickup::Pickup() : FeatureCore("Pickup", TYPE_PLAYERS)
{
	DECLARE_CONFIG(GetConfigManager(), "CustomThrow", float, 3.f);
	DECLARE_CONFIG(GetConfigManager(), "ThrowMultiplier", bool, false);
	DECLARE_CONFIG(GetConfigManager(), "PickupEverything", bool, false);
	DECLARE_CONFIG(GetConfigManager(), "CustomGrabDistance", float, 3.f);
	DECLARE_CONFIG(GetConfigManager(), "GrabDistanceMultiplier", bool, false);
	DECLARE_CONFIG(GetConfigManager(), "PocketEverything", bool, false);

	SDK::Init_Call_ForceDrop();
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
		bool PocketEverything = CONFIG_BOOL(GetConfigManager(), "PocketEverything");
		bool PickupEverything = CONFIG_BOOL(GetConfigManager(), "PickupEverything");

		if (ImGui::Checkbox("Custom throw", &ThrowMultiplier))
			SET_CONFIG_VALUE(GetConfigManager(), "ThrowMultiplier", bool, ThrowMultiplier);
		if (ImGui::SliderFloat("Throw multiplier", &CustomThrow, 1.f, 100.0f, "%.1fx"))
			SET_CONFIG_VALUE(GetConfigManager(), "CustomThrow", float, CustomThrow);

		if (ImGui::Checkbox("Custom grab distance", &GrabDistanceMultiplier));
			SET_CONFIG_VALUE(GetConfigManager(), "GrabDistanceMultiplier", bool, GrabDistanceMultiplier);
		if (ImGui::SliderFloat("Grab distance", &CustomGrabDistance, 1.f, 50.0f, "%.1f units"))
			SET_CONFIG_VALUE(GetConfigManager(), "CustomGrabDistance", float, CustomGrabDistance);
		if (ImGui::Checkbox("Pickup Everything", &PickupEverything))
			SET_CONFIG_VALUE(GetConfigManager(), "PickupEverything", bool, PickupEverything);
		if (ImGui::Checkbox("Pocket Everything", &PocketEverything)) // DashaAngelBars offered this feature.
		{
			SET_CONFIG_VALUE(GetConfigManager(), "PocketEverything", bool, PocketEverything);
			PocketEverything ? SDK::Call_ForceDrop_off() : SDK::Call_ForceDrop_on();
		}
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
	if (CONFIG_BOOL(GetConfigManager(), "PickupEverything"))
	{
		for (auto* obj : InGame::photonInstances)
		{
			if (!obj) return;

			obj->Fields.isProp = true;
			obj->Fields.isItem = true;
			obj->Fields.isDroppable = true;
			obj->Fields.isUsable = true;
		}
	}
	if (CONFIG_BOOL(GetConfigManager(), "ThrowMultiplier"))
	{
		for (auto* obj : InGame::photonInstances)
		{
			if (!obj) return;

			obj->Fields.throwMultiplier = CONFIG_FLOAT(GetConfigManager(), "CustomThrow");
		}
	}
}
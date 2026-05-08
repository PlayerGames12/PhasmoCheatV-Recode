#include "spiritboxalw.h"

using namespace PhasmoCheatV::Features::Misc;

SpiritBoxAlwaysAnswer::SpiritBoxAlwaysAnswer() : FeatureCore(LANG("SpiritBoxAlwaysAnswer_Header"), TYPE_MISC) {}

void SpiritBoxAlwaysAnswer::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("EnableSpiritBoxAlw"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}

	ImGui::PopStyleVar();
}
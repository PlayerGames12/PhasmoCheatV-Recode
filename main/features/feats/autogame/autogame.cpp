#include "autogame.h"

using namespace PhasmoCheatV::Features::Misc;

AutoGame::AutoGame() : FeatureCore(LANG("AutoGame_Header"), TYPE_MISC)
{
	DECLARE_CONFIG(GetConfigManager(), "AutoGameDelay", int, 5);
}

void AutoGame::OnRender()
{
	// This fPeature is private. lease wait for release to see it in action.
}

void AutoGame::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));
	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("EnableAutoGame"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		enabled ? OnActivate() : OnDeactivate();
	}
	if (!enabled)
	{
		ImGui::PopStyleVar();
		return;
	}
	int delay = CONFIG_INT(GetConfigManager(), "AutoGameDelay");
	if (ImGui::SliderInt(LANG("AutoGameDelay"), &delay, 1, 30))
		SET_CONFIG_VALUE(GetConfigManager(), "AutoGameDelay", int, delay);
	ImGui::PopStyleVar();
}

void AutoGame::AutoGameHandler()
{
	// This feature is private. Please wait for release to see it in action.
}
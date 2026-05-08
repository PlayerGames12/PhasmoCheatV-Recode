#include "notifyinfo.h"

using namespace PhasmoCheatV::Features::Visuals;

NotifyInfo::NotifyInfo() : FeatureCore(LANG("NotifyInfo_Header"), TYPE_VISUALS) 
{
	DECLARE_CONFIG(GetConfigManager(), "HuntingNotify", bool, true);
	DECLARE_CONFIG(GetConfigManager(), "CollectBoneNotify", bool, false);
}

void NotifyInfo::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));
	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("EnableNotifyInfo"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
	ImGui::PopStyleVar();
}

void NotifyInfo::RenderNotifyHunt(SDK::GhostAI* ghostAI, bool Hunting)
{
	if (!IsActive()) return;

	std::string txt;
	if (isHunting == false && Hunting == false)
		txt = LANG("GhostTriedHunt");
	else
		txt = Hunting ? LANG("GhostStartHunting") : LANG("GhostStopHunting");

	NOTIFY_WARNING_QUICK(txt);
}

void NotifyInfo::RenderNotifyBone()
{
	if (!IsActive()) return;

	NOTIFY_INFO_QUICK(LANG("BoneCollected"));
}

#include "notifyinfo.h"

using namespace PhasmoCheatV::Features::Visuals;

NotifyInfo::NotifyInfo() : FeatureCore("Notify Info", TYPE_VISUALS) 
{
	DECLARE_CONFIG(GetConfigManager(), "HuntingNotify", bool, true);
	DECLARE_CONFIG(GetConfigManager(), "CollectBoneNotify", bool, false);
}

void NotifyInfo::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));
	bool enabled = IsActive();
	if (ImGui::Checkbox("Enable Notify Info", &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
	ImGui::PopStyleVar();
}

void NotifyInfo::RenderNotifyHunt(SDK::GhostAI* ghostAI, bool Hunting)
{
	std::string txt;
	if (isHunting == false && Hunting == false)
		txt = "Ghost tried to hunt.";
	else
		txt = Hunting ? "Ghost started hunting." : "Ghost stopped hunting.";

	NOTIFY_WARNING_QUICK(txt);
}

void NotifyInfo::RenderNotifyBone()
{
	NOTIFY_INFO_QUICK("Bone has been collected.");
}
#include "skiplayeranim.h"

using namespace PhasmoCheatV::Features::Players;

SkipLayerAnim::SkipLayerAnim() : FeatureCore(LANG("SkipLayerAnim_Header"), TYPE_PLAYERS) {}

void SkipLayerAnim::OnActivate()
{
	auto* localPlayer = Utils::GetLocalPlayer();
	if (!localPlayer)
	{
		NOTIFY_ERROR_QUICK(LANG("LocalPlayerNotFound"));
		return;
	}
	auto* lAnimator = localPlayer->Fields.Animator;
	if (!lAnimator)
	{
		NOTIFY_ERROR_QUICK(LANG("LocalPlayerNotFound"));
		return;
	}

	SDK::Animator_Set_Speed(lAnimator, 999999.f, nullptr); // Don't use FLT_MAX pls
}

void SkipLayerAnim::OnDeactivate()
{
	auto* localPlayer = Utils::GetLocalPlayer();
	if (!localPlayer)
	{
		NOTIFY_ERROR_QUICK(LANG("LocalPlayerNotFound"));
		return;
	}
	auto* lAnimator = localPlayer->Fields.Animator;
	if (!lAnimator)
	{
		NOTIFY_ERROR_QUICK(LANG("LocalPlayerNotFound"));
		return;
	}

	SDK::Animator_Set_Speed(lAnimator, 1.f, nullptr);
}

void SkipLayerAnim::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));
	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("SkipPlayerAnimEnable"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
	ImGui::PopStyleVar();
}

void SkipLayerAnim::SkipLayerAnimHandler()
{
	auto* localPlayer = Utils::GetLocalPlayer();
	if (!IsActive() || !localPlayer || !localPlayer->Fields.Animator)
		return;

	SDK::Animator_Set_Speed(localPlayer->Fields.Animator, 999999.f, nullptr); // Don't use FLT_MAX pls
}	
#include "ghosthandstand.h"

using namespace PhasmoCheatV::Features::Misc;

GhostHandstand::GhostHandstand() : FeatureCore(LANG("GhostHandstand_Header"), TYPE_MISC) {}

void GhostHandstand::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("GhostHandstandEnabled"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}

	ImGui::PopStyleVar();
}

void GhostHandstand::GhostHandstandMain(SDK::GhostAI* ghostAI)
{
	if (!ghostAI || !ghostAI->Fields.raycastPoint || !ghostAI->Fields.feetRaycastPoint) return;

	auto* bodyTransform = SDK::Transform_Get_Parent(ghostAI->Fields.raycastPoint, nullptr);
	if (!bodyTransform) return;

	if (!IsActive())
	{
		if (m_applied)
		{
			SDK::Transform_Set_localScale(bodyTransform, normalScale, nullptr);
			m_applied = false;
		}
		return;
	}

	// Calculate model height once on first frame (before scale flip)
	if (!m_applied)
	{
		float topY  = SDK::Transform_Get_Position(ghostAI->Fields.raycastPoint, nullptr).Y;
		float feetY = SDK::Transform_Get_Position(ghostAI->Fields.feetRaycastPoint, nullptr).Y;
		m_height = topY - feetY;
		if (m_height <= 0.0f) m_height = 1.8f;
	}

	auto pos = SDK::Transform_Get_Position(bodyTransform, nullptr);
	pos.Y += m_height;

	SDK::Transform_Set_localScale(bodyTransform, flippedScale, nullptr);
	SDK::Transform_Set_Position(bodyTransform, pos, nullptr);

	m_applied = true;
}

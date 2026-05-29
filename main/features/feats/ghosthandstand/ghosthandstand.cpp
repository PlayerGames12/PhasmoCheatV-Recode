#include "ghosthandstand.h"

using namespace PhasmoCheatV::Features::Misc;

// 180 degrees around X axis: (sin(pi/2), 0, 0, cos(pi/2)) = (1, 0, 0, 0)
static const SDK::Quaternion handstandQuat = { 1.0f, 0.0f, 0.0f, 0.0f };
static const SDK::Quaternion identityQuat   = { 0.0f, 0.0f, 0.0f, 1.0f };

GhostHandstand::GhostHandstand() : FeatureCore(LANG("GhostHandstand_Header"), TYPE_MISC)
{
}

void GhostHandstand::OnMenuRender()
{
	bool enabled = IsActive();
	if (BCheckBox(LANG("GhostHandstandEnabled"), &enabled, "b_GhostHandstandEnabled"))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
}

void GhostHandstand::GhostHandstandMain(SDK::GhostAI* ghostAI)
{
	if (!ghostAI || !ghostAI->Fields.raycastPoint) return;

	auto* bodyTransform = SDK::Transform_Get_Parent(ghostAI->Fields.raycastPoint, nullptr);
	if (!bodyTransform) return;

	if (IsActive())
	{
		float ghostHeight = 0.0f;
		if (ghostAI->Fields.raycastPoint && ghostAI->Fields.feetRaycastPoint)
		{
			auto top = SDK::Transform_Get_Position(ghostAI->Fields.raycastPoint, nullptr);
			auto bottom = SDK::Transform_Get_Position(ghostAI->Fields.feetRaycastPoint, nullptr);
			ghostHeight = top.Y - bottom.Y;
		}
		if (ghostHeight <= 0.0f) ghostHeight = 1.8f;

		SDK::Transform_Set_Rotation(bodyTransform, handstandQuat, nullptr);

		auto pos = SDK::Transform_Get_Position(bodyTransform, nullptr);
		pos.Y += ghostHeight;
		SDK::Transform_Set_Position(bodyTransform, pos, nullptr);

		m_applied = true;
		m_offsetY = ghostHeight;
	}
	else if (m_applied)
	{
		SDK::Transform_Set_Rotation(bodyTransform, identityQuat, nullptr);

		auto pos = SDK::Transform_Get_Position(bodyTransform, nullptr);
		pos.Y -= m_offsetY;
		SDK::Transform_Set_Position(bodyTransform, pos, nullptr);

		m_applied = false;
	}
}

#include "ghosthandstand.h"

using namespace PhasmoCheatV::Features::Misc;

static const SDK::Vector3 flippedScale  = { 1.0f, -1.0f, 1.0f };
static const SDK::Vector3 normalScale   = { 1.0f,  1.0f, 1.0f };

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

	if (!IsActive())
	{
		if (m_basePosSet)
		{
			SDK::Transform_Set_localScale(bodyTransform, normalScale, nullptr);
			SDK::Transform_Set_Position(bodyTransform, m_baseBodyPos, nullptr);
			m_basePosSet = false;
		}
		return;
	}

	// Capture base position and model height on first active frame
	if (!m_basePosSet)
	{
		m_baseBodyPos = SDK::Transform_Get_Position(bodyTransform, nullptr);
		if (ghostAI->Fields.feetRaycastPoint)
		{
			auto top = SDK::Transform_Get_Position(ghostAI->Fields.raycastPoint, nullptr);
			auto bottom = SDK::Transform_Get_Position(ghostAI->Fields.feetRaycastPoint, nullptr);
			m_modelHeight = top.Y - bottom.Y;
		}
		if (m_modelHeight <= 0.0f) m_modelHeight = 1.8f;
		m_basePosSet = true;
	}

	SDK::Transform_Set_localScale(bodyTransform, flippedScale, nullptr);

	auto pos = m_baseBodyPos;
	pos.Y += m_modelHeight;
	SDK::Transform_Set_Position(bodyTransform, pos, nullptr);
}

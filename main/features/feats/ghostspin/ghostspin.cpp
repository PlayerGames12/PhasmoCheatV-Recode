#include "ghostspin.h"
#include <cmath>

using namespace PhasmoCheatV::Features::Misc;

GhostSpin::GhostSpin() : FeatureCore(LANG("GhostSpin_Header"), TYPE_MISC)
{
	DECLARE_CONFIG(GetConfigManager(), "Speed", float, 360.0f);
}

void GhostSpin::OnMenuRender()
{
	bool enabled = IsActive();
	float speed = CONFIG_FLOAT(GetConfigManager(), "Speed");
	if (BCheckBox(LANG("GhostSpinEnabled"), &enabled, "b_GhostSpinEnabled"))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
	if (ImGui::SliderFloat(LANG("GhostSpinSpeed"), &speed, 0.0f, 2000.0f, "%.0f deg/s"))
		SET_CONFIG_VALUE(GetConfigManager(), "Speed", float, speed);
}

void GhostSpin::GhostSpinMain(SDK::GhostAI* ghostAI)
{
	if (!IsActive()) return;
	if (!ghostAI || !ghostAI->Fields.raycastPoint) return;

	auto* bodyTransform = SDK::Transform_Get_Parent(ghostAI->Fields.raycastPoint, nullptr);
	if (!bodyTransform) return;

	// Capture base position and model height on first frame
	if (!m_basePosSet) {
		m_baseBodyPos = SDK::Transform_Get_Position(bodyTransform, nullptr);
		if (ghostAI->Fields.feetRaycastPoint) {
			SDK::Vector3 top = SDK::Transform_Get_Position(ghostAI->Fields.raycastPoint, nullptr);
			SDK::Vector3 bottom = SDK::Transform_Get_Position(ghostAI->Fields.feetRaycastPoint, nullptr);
			m_modelHeight = top.Y - bottom.Y;
		}
		if (m_modelHeight <= 0.0f) m_modelHeight = 1.8f;
		m_basePosSet = true;
	}

	float speed = CONFIG_FLOAT(GetConfigManager(), "Speed");
	float dt = SDK::Time_Get_DeltaTime(nullptr);
	m_spinAngle += speed * dt * 0.0174533f;
	if (m_spinAngle > 6.2831853f) m_spinAngle -= 6.2831853f;

	float halfAngle = m_spinAngle * 0.5f;
	SDK::Quaternion yRot = { 0.0f, sinf(halfAngle), 0.0f, cosf(halfAngle) };

	// Raise body up when inverted to prevent clipping into ground
	SDK::Vector3 bodyPos = m_baseBodyPos;
	float t = fabsf(sinf(m_spinAngle));
	bodyPos.Y += m_modelHeight * t;
	SDK::Transform_Set_Position(bodyTransform, bodyPos, nullptr);

	SDK::Transform_Set_Rotation(bodyTransform, yRot, nullptr);
}

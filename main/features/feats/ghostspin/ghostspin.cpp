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

	float speed = CONFIG_FLOAT(GetConfigManager(), "Speed");
	float dt = SDK::Time_Get_DeltaTime(nullptr);
	m_spinAngle += speed * dt * 0.0174533f;
	if (m_spinAngle > 6.2831853f) m_spinAngle -= 6.2831853f;

	float halfAngle = m_spinAngle * 0.5f;
	SDK::Quaternion yRot = { 0.0f, sinf(halfAngle), 0.0f, cosf(halfAngle) };

	SDK::Transform_Set_Rotation(bodyTransform, yRot, nullptr);
}

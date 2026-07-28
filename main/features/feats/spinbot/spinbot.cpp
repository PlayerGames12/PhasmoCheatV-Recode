#include "spinbot.h"
#include <cmath>

using namespace PhasmoCheatV::Features::Misc;

Spinbot::Spinbot() : FeatureCore(LANG("Spinbot_Header"), TYPE_MISC)
{
	DECLARE_CONFIG(GetConfigManager(), "Speed", float, 360.0f);
}

void Spinbot::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("SpinbotEnabled"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}

	if (enabled)
	{
		float speed = CONFIG_FLOAT(GetConfigManager(), "Speed");
		if (ImGui::SliderFloat(LANG("SpinbotSpeed"), &speed, 0.0f, 2000.0f, "%.0f deg/s"))
			SET_CONFIG_VALUE(GetConfigManager(), "Speed", float, speed);
	}

	ImGui::PopStyleVar();
}

void Spinbot::SpinbotMain(SDK::FirstPersonController* firstPersonController)
{
	if (!IsActive()) return;

	auto* player = Utils::GetLocalPlayer();
	if (!player || !player->Fields.LocalPlayer) return;

	auto* camera = player->Fields.LocalPlayer->Fields.Camera;
	if (!camera) return;

	auto* bodyTransform = SDK::Component_Get_Transform(
		reinterpret_cast<SDK::Component*>(firstPersonController), nullptr);
	auto* cameraTransform = SDK::Component_Get_Transform(
		reinterpret_cast<SDK::Component*>(camera), nullptr);
	if (!bodyTransform || !cameraTransform) return;

	SDK::Quaternion savedCameraRot = SDK::Transform_Get_Rotation(cameraTransform, nullptr);

	float speed = CONFIG_FLOAT(GetConfigManager(), "Speed");
	float dt = SDK::Time_Get_DeltaTime(nullptr);
	m_spinAngle += speed * dt * 0.0174533f; // deg to rad
	if (m_spinAngle > 6.2831853f) m_spinAngle -= 6.2831853f;

	float halfAngle = m_spinAngle * 0.5f;
	SDK::Quaternion yRot = { 0.0f, sinf(halfAngle), 0.0f, cosf(halfAngle) };

	SDK::Transform_Set_Rotation(bodyTransform, yRot, nullptr);
	SDK::Transform_Set_Rotation(cameraTransform, savedCameraRot, nullptr);
}

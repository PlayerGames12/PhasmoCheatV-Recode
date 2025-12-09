#include "noclip.h"

using namespace PhasmoCheatV::Features::Movement; // Many thanks to Evelien for NoClip

NoClip::NoClip() : FeatureCore("NoClip", TYPE_MOVEMENT)
{
	DECLARE_CONFIG(GetConfigManager(), "NoClipSpeed", float, 1.f);
}

void NoClip::OnMenuRender()
{
	bool enabled = IsActive();
	float noClipSpeed = CONFIG_FLOAT(GetConfigManager(), "NoClipSpeed");

	ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "Thanks to Evelien for the NoClip feature!");
	if (ImGui::Checkbox("Enabled##noclip", &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
	if (ImGui::SliderFloat("Speed##noclip", &noClipSpeed, 0.0f, 10.0f, "%.1f"))
		SET_CONFIG_VALUE(GetConfigManager(), "NoClipSpeed", float, noClipSpeed);
}

void NoClip::OnDeactivate()
{
	auto localPlayer = Utils::GetLocalPlayer();
	if (localPlayer)
	{
		auto firstPersonController = localPlayer->Fields.FirstPersonController;
		if (firstPersonController)
		{
			const auto controller = firstPersonController->Fields.PhysicsCharacterController;
			const auto rigidBody = controller->Fields.Rigidbody;

			SDK::Behaviour_Set_Enabled(reinterpret_cast<SDK::Behaviour*>(controller), true, nullptr);
			SDK::Rigidbody_Set_IsKinematic(rigidBody, false, nullptr);

			SDK::Rigidbody_Set_Position(rigidBody, SDK::Transform_Get_Position(
				SDK::Component_Get_Transform(reinterpret_cast<SDK::Component*>(controller), nullptr),
				nullptr
			), nullptr);
		}
	}
}

void NoClip::NoClipMain(SDK::FirstPersonController* firstPersonController)
{
    const auto& enabled = IsActive();
    const auto controller = firstPersonController->Fields.PhysicsCharacterController;
    const auto rigidBody = controller->Fields.Rigidbody;
    if (!enabled)
    {
        if (SDK::Rigidbody_Get_IsKinematic(rigidBody, nullptr))
        {
            SDK::Rigidbody_Set_IsKinematic(rigidBody, false, nullptr);
        }
        if (!SDK::Behaviour_Get_Enabled(reinterpret_cast<SDK::Behaviour*>(controller), nullptr))
        {
            SDK::Behaviour_Set_Enabled(reinterpret_cast<SDK::Behaviour*>(controller), true, nullptr);
        }
        return;
    }
    const HWND foregroundWindow = GetForegroundWindow();
    DWORD foregroundProcessId = 0;
    GetWindowThreadProcessId(foregroundWindow, &foregroundProcessId);
    if (foregroundProcessId != GetCurrentProcessId() || menu.Open)
        return;
    if (!SDK::Rigidbody_Get_IsKinematic(rigidBody, nullptr))
    {
        SDK::Rigidbody_Set_IsKinematic(rigidBody, true, nullptr);
    }
    if (SDK::Behaviour_Get_Enabled(reinterpret_cast<SDK::Behaviour*>(controller), nullptr))
    {
        SDK::Behaviour_Set_Enabled(reinterpret_cast<SDK::Behaviour*>(controller), false, nullptr);
    }
    const auto transform = SDK::Component_Get_Transform(reinterpret_cast<SDK::Component*>(controller), nullptr);

    SDK::Camera* camera = Utils::GetLocalPlayer()->Fields.Camera;
    const auto camTransform = SDK::Component_Get_Transform(reinterpret_cast<SDK::Component*>(camera), nullptr);

    const auto forward = SDK::Transform_Get_Forward(camTransform, nullptr);
    const auto right = SDK::Transform_Get_Right(camTransform, nullptr); 
    const auto up = SDK::Transform_Get_Up(transform, nullptr);

    SDK::Vector3 position = {};
    const uint8_t movementMask = (GetAsyncKeyState(0x57) ? 1 : 0) |
        (GetAsyncKeyState(0x53) ? 2 : 0) |
        (GetAsyncKeyState(0x44) ? 4 : 0) |
        (GetAsyncKeyState(0x41) ? 8 : 0) |
        (GetAsyncKeyState(VK_LSHIFT) ? 16 : 0) |
        (GetAsyncKeyState(VK_LCONTROL) ? 32 : 0);
    if (movementMask & 1)
        position += forward;
    if (movementMask & 2)
        position -= forward;
    if (movementMask & 4)
        position += right;
    if (movementMask & 8)
        position -= right;
    if (movementMask & 16)
        position += up;
    if (movementMask & 32)
        position -= up;
    const auto speed = CONFIG_FLOAT(GetConfigManager(), "NoClipSpeed") * SDK::Time_Get_DeltaTime(nullptr);
    position *= speed;
    position += SDK::Transform_Get_Position(transform, nullptr);
    SDK::Transform_Set_Position(transform, position, nullptr);
    SDK::Rigidbody_Set_Position(rigidBody, position, nullptr);
}
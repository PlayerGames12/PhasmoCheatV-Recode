#include "fullbright.h"

using namespace PhasmoCheatV::Features::Visuals;

Fullbright::Fullbright() : FeatureCore("Fullbright", TYPE_VISUALS)
{
    DECLARE_CONFIG(GetConfigManager(), "Intensity", float, 1.f);
}

void Fullbright::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox("Enable Fullbright", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled) {
        float intensity = CONFIG_FLOAT(GetConfigManager(), "Intensity");

        if (ImGui::SliderFloat("##Intensity", &intensity, 0.1f, 100.f, "%.1f intensity"))
            SET_CONFIG_VALUE(GetConfigManager(), "Intensity", float, intensity);

        if (ImGui::Button("Force Apply"))
            FullbrightMain();
    }

    ImGui::PopStyleVar();
}

void Fullbright::OnDeactivate() {
    if (InGame::FBGO) {
        SDK::Object_Destroy((SDK::Object*)InGame::FBGO, nullptr);
        InGame::FBGO = nullptr;
    }
}

void Fullbright::FullbrightMain() {
    SDK::String* fbName = Utils::SysStrToUnityStr("VComTeamLight");
    SDK::GameObject* gameObject = SDK::GameObject_Find(fbName, nullptr);

    if (!IsActive()) {
        if (gameObject) {
            SDK::Object_Destroy((SDK::Object*)gameObject, nullptr);
        }
        return;
    }

    float intensity = CONFIG_FLOAT(GetConfigManager(), "Intensity");

    if (!gameObject) {
        gameObject = (SDK::GameObject*)CreateIl2CppObject("UnityEngine.CoreModule", "UnityEngine", "GameObject");
        if (!gameObject) return;
        SDK::Object_set_name((SDK::Object*)gameObject, fbName, nullptr);

        SDK::String* lightTypeName = Utils::SysStrToUnityStr("UnityEngine.Light, UnityEngine.CoreModule");
        if (!lightTypeName) return;
        SDK::Type* lightType = SDK::System_Type_GetType(lightTypeName, nullptr);
        if (!lightType) return;
        SDK::Component* lightComponent = SDK::GameObject_AddComponent(gameObject, lightType, nullptr);
        if (!lightComponent) return;
        SDK::Light* light = (SDK::Light*)lightComponent;
        SDK::Light_intensity_set(light, intensity, nullptr);
        SDK::Light_type_set(light, SDK::LightType::Directional, nullptr);
        SDK::Light_shadows_set(light, SDK::ShadowsType::None, nullptr);
        SDK::Light_renderMode_set(light, SDK::RenderMode::ForceVertex, nullptr);
        SDK::GameObject_SetActive(gameObject, true, nullptr);
    }
    else {
        SDK::Light* light = reinterpret_cast<SDK::Light*>(
            SDK::GameObject_GetComponent(
                gameObject,
                SDK::System_Type_GetType(
                    Utils::SysStrToUnityStr("UnityEngine.Light, UnityEngine.CoreModule"),
                    nullptr
                ),
                nullptr
            )
            );
        if (light) {
            SDK::Light_intensity_set(light, intensity, nullptr);
        }
        if (!SDK::GameObject_get_activeSelf(gameObject, nullptr)) {
            SDK::GameObject_SetActive(gameObject, true, nullptr);
        }
    }

    auto localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer) return;
    auto lightTransform = SDK::GameObject_get_transform(gameObject, nullptr);
    if (!lightTransform) return;
    auto cameraTransform = Utils::GetPlayerTransformCamera(localPlayer);
    if (!cameraTransform) return;
    auto currentParent = SDK::Transform_Get_Parent(lightTransform, nullptr);
    if (currentParent != cameraTransform) {
        SDK::Transform_Set_Parent(lightTransform, cameraTransform, nullptr);
    }
    SDK::Transform_Set_Position(lightTransform, Utils::GetPosVec3(localPlayer), nullptr);
    SDK::Transform_Set_Rotation(lightTransform, SDK::identityQuaternion, nullptr);
}
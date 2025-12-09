#include "foveditor.h"

using namespace PhasmoCheatV::Features::Players;

FoVEditor::FoVEditor() : FeatureCore("FoVEditor", TYPE_PLAYERS)
{
    DECLARE_CONFIG(GetConfigManager(), "CustomFoVValue", float, 90.f);
    DECLARE_CONFIG(GetConfigManager(), "DefaultFoVValue", float, 90.f);
    DECLARE_CONFIG(GetConfigManager(), "DefaultFoVSaved", bool, false);
}

void FoVEditor::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));
    bool enabled = IsActive();
    if (ImGui::Checkbox("Enable custom FoV", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled)
    {
        ImGui::Spacing();
        float customFoV = CONFIG_FLOAT(GetConfigManager(), "CustomFoVValue");
        if (ImGui::SliderFloat("Custom FoV Value", &customFoV, 10.0f, 170.0f, "%.1f"))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "CustomFoVValue", float, customFoV);
        }
        ImGui::Spacing();
        if (ImGui::Button("Force Apply", ImVec2(120, 30)))
        {
            FoVEditorMain();
        }
        if (ImGui::Button("Reset to Default"))
        {
            float defaultFoV = CONFIG_FLOAT(GetConfigManager(), "DefaultFoVValue");
            SET_CONFIG_VALUE(GetConfigManager(), "CustomFoVValue", float, defaultFoV);
        }
    }
    ImGui::PopStyleVar();
}

void FoVEditor::FoVEditorMain()
{
    auto localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer) return;
    auto Camera = localPlayer->Fields.Camera;
    if (!Camera) return;
    float defFoV = SDK::Camera_Get_FieldOfView(Camera, nullptr);
    bool saved = CONFIG_BOOL(GetConfigManager(), "DefaultFoVSaved");
    if (!saved)
    {
        SET_CONFIG_VALUE(GetConfigManager(), "DefaultFoVValue", float, defFoV);
        SET_CONFIG_VALUE(GetConfigManager(), "DefaultFoVSaved", bool, true);
    }
    float custFoV = CONFIG_FLOAT(GetConfigManager(), "CustomFoVValue");
    if (custFoV != SDK::Camera_Get_FieldOfView(Camera, nullptr))
        SDK::Camera_Set_FieldOfView(Camera, custFoV, nullptr);
}
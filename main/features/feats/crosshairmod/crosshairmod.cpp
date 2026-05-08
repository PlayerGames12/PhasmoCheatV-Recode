#include "crosshairmod.h"

using namespace PhasmoCheatV::Features::Players;

CrosshairModifier::CrosshairModifier() : FeatureCore(LANG("CrosshairModifier_Header"), TYPE_PLAYERS)
{
    DECLARE_CONFIG(GetConfigManager(), "CrosshairColor", ImColor, ImColor(255, 100, 255, 255));
    DECLARE_CONFIG(GetConfigManager(), "IsRGB", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "CrosshairSize", float, 1.0f);
}

void CrosshairModifier::OnMenuRender()
{
    const auto localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer)
    {
        ImGui::Text(LANG("NeedToBeInGame"));
        return;
    }

    bool enabled = IsActive();
    if (ImGui::Checkbox(LANG("CrosshairModifierEnable"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (!enabled)
        return;

    ImColor configColor = CONFIG_COLOR(GetConfigManager(), "CrosshairColor");

    ImVec4 editColor = ImVec4(
        configColor.Value.x,
        configColor.Value.y,
        configColor.Value.z,
        configColor.Value.w
    );

    ImGui::PushID("CrosshairColorPicker");

    if (ImGui::ColorEdit4("##color", (float*)&editColor,
        ImGuiColorEditFlags_NoInputs |
        ImGuiColorEditFlags_NoLabel |
        ImGuiColorEditFlags_AlphaPreview))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "CrosshairColor", ImColor,
            ImColor(
                editColor.x,
                editColor.y,
                editColor.z,
                editColor.w
            )
        );
    }
    ImGui::SameLine();
    bool isRGB = CONFIG_BOOL(GetConfigManager(), "IsRGB");
    if (ImGui::Checkbox(LANG("RGBModeTr"), &isRGB))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "IsRGB", bool, isRGB);
    }

    float size = CONFIG_FLOAT(GetConfigManager(), "CrosshairSize");
    if (ImGui::SliderFloat(LANG("CrosshairSizeTr"), &size, 0.1f, 5.0f, "%.2f"))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "CrosshairSize", float, size);
    }

    ImGui::PopID();
}

void CrosshairModifier::CrosshairModifierMain()
{
    if (!IsActive()) return;

    const auto localPlayer = Utils::GetLocalPlayer(); if (!localPlayer) return;
    auto* obj_cr = Utils::GetPlayerCrosshairObj(localPlayer); if (!obj_cr) return;
    auto* comp_cr = SDK::GameObject_GetComponentByName(obj_cr, Utils::SysStrToUnityStr("UnityEngine.UI.Image"), nullptr); if (!comp_cr) return;
    auto* rectType = SDK::System_Type_GetType(Utils::SysStrToUnityStr("UnityEngine.RectTransform"), nullptr);
    if (!rectType)
    {
        LOG_ERROR("RectType not found!");
        return;
    }
    auto* rectTransform = SDK::GameObject_GetComponent(obj_cr, rectType, nullptr); 
    if (!rectTransform)
    {
        LOG_ERROR("RectTransform not found!"); 
        return;
    }

    bool isRGB = CONFIG_BOOL(GetConfigManager(), "IsRGB");
    ImColor cfgColor = CONFIG_COLOR(GetConfigManager(), "CrosshairColor");
    float sizeMultiplier = CONFIG_FLOAT(GetConfigManager(), "CrosshairSize");

    static float hue = 0.0f;
    static bool sizeInitialized = false;
    static SDK::Vector2 originalSize;

    ImVec4 finalColor;

    if (isRGB)
    {
        hue += 0.0025f;
        if (hue > 1.0f)
            hue = 0.0f;

        finalColor = Utils::HSV2RGB(hue, 1.0f, 1.0f);
        finalColor.w = cfgColor.Value.w;
    }
    else
    {
        finalColor = cfgColor.Value;
    }

    SDK::Color sdkColor;
    sdkColor.R = finalColor.x;
    sdkColor.G = finalColor.y;
    sdkColor.B = finalColor.z;
    sdkColor.A = finalColor.w;

    SDK::Graphic_set_Color((SDK::Graphic*)comp_cr, sdkColor, nullptr);

    if (!sizeInitialized)
    {
        originalSize = SDK::RectTransform_get_sizeDelta(
            (SDK::RectTransform*)rectTransform,
            nullptr
        );
        sizeInitialized = true;
    }

    SDK::Vector2 newSize;
    newSize.X = originalSize.X * sizeMultiplier;
    newSize.Y = originalSize.Y * sizeMultiplier;

    SDK::RectTransform_set_sizeDelta(
        (SDK::RectTransform*)rectTransform,
        newSize,
        nullptr
    );
}
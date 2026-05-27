#include "worldmodulation.h" // code by @softvoidds

using namespace PhasmoCheatV::Features::Visuals;

WorldModulation::WorldModulation()
    : FeatureCore(LANG("WorldModulation_Header"), TYPE_VISUALS)
{
    DECLARE_CONFIG(GetConfigManager(), "Color", ImColor, ImColor(255, 255, 255, 255));
    DECLARE_CONFIG(GetConfigManager(), "AffectMaterials", bool, true);
}

void WorldModulation::OnActivate()
{
    Cache.affectMaterials = CONFIG_BOOL(GetConfigManager(), "AffectMaterials");

    ImColor c = CONFIG_COLOR(GetConfigManager(), "Color");
    Cache.color = { c.Value.x, c.Value.y, c.Value.z, c.Value.w };
}

void WorldModulation::OnDeactivate()
{
    RestoreOriginalMaterials();
}

void WorldModulation::OnRender()
{
    if (IsActive())
        ApplyModulation();
}

void WorldModulation::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();

    if (BCheckBox(LANG("EnableWorldModulation"), &enabled, "b_WorldMod"))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled)
    {
        if (ImGui::ColorEdit4((std::string(LANG("Color")) + "##WorldMod").c_str(), (float*)&Cache.color))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "Color", ImColor, ImColor(Cache.color.R, Cache.color.G, Cache.color.B, Cache.color.A));
        }

        if (ImGui::Checkbox(LANG("AffectMaterials"), &Cache.affectMaterials))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "AffectMaterials", bool, Cache.affectMaterials);
        }
    }

    ImGui::PopStyleVar();
}

void WorldModulation::ApplyModulation()
{
    if (!Cache.affectMaterials)
        return;

    auto* rendererType = Utils::GetType("UnityEngine.Renderer");
    if (!rendererType)
        return;

    auto* arr = SDK::Object_FindObjectsOfType(rendererType, nullptr);
    if (!arr)
        return;

    for (uint32_t i = 0; i < arr->MaxLength; i++)
    {
        auto* r = (SDK::Render*)arr->Vector[i];
        if (!r) continue;

        auto* mat = SDK::Render_get_sharedMaterial(r, nullptr);
        if (!mat) continue;

        SDK::Material_set_color(mat,
            SDK::Color{ Cache.color.R, Cache.color.G, Cache.color.B, Cache.color.A },
            nullptr);
    }
}
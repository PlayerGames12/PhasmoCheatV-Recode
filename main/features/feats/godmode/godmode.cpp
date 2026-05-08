#include "godmode.h"

using namespace PhasmoCheatV::Features::Players;

GodMode::GodMode() : FeatureCore(LANG("GodMode_Header"), TYPE_PLAYERS) {}

void GodMode::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (BCheckBox(LANG("GodModeEnable"), &enabled, "b_GodModeEnable"))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    ImGui::PopStyleVar();
}
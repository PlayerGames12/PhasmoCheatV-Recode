#include "godmode.h"

using namespace PhasmoCheatV::Features::Players;

GodMode::GodMode() : FeatureCore("GodMode", TYPE_PLAYERS) {}

void GodMode::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox("Enable GodMode", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    ImGui::PopStyleVar();
}
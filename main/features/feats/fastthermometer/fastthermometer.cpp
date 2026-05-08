#include "fastthermometer.h"

using namespace PhasmoCheatV::Features::Misc;

FastThermometer::FastThermometer() : FeatureCore(LANG("FastThermometer_Header"), TYPE_MISC) {}

void FastThermometer::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox(LANG("FastThermometerEnable"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled)
        ImGui::Text(LANG("FastThermometerInfo"));

    ImGui::PopStyleVar();
}

void FastThermometer::FastThermometerMain(SDK::Thermometer* thermometer)
{
    if (!IsActive()) return;
    if (!thermometer) return;

    thermometer->Fields.measureTimer = 0.2f;
}
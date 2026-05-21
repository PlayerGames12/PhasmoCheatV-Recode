#include "temperaturepanel.h"

using namespace PhasmoCheatV::Features::Visuals;

TemperaturePanel::TemperaturePanel() : FeatureCore(LANG("TemperaturePanel_Header"), TYPE_VISUALS) {}

void TemperaturePanel::OnRender()
{
    if (!IsActive())
        return;

    const auto localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer || !localPlayer->Fields.LevelRoom)
    {
        LOG_INFO(localPlayer ? "LevelRoom is null" : "Local player is null");
        return;
    }

    const float temperature = localPlayer->Fields.LevelRoom->Fields.temperature;

    ImVec4 tempColor;
    if (temperature <= 0.f)
        tempColor = ImVec4(0.4f, 0.7f, 1.0f, 1.0f);
    else if (temperature <= 15.f)
        tempColor = ImVec4(0.6f, 0.9f, 0.6f, 1.0f);
    else 
        tempColor = ImVec4(1.0f, 0.6f, 0.4f, 1.0f);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(16, 14));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.f);

    ImGui::SetNextWindowSize(ImVec2(220, 110), ImGuiCond_Once);
    ImGui::Begin("###TemperatureWindow", nullptr, Globals::WINDOW_FLAGS_GLOBALS);

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::TextColored(ImVec4(0.7f, 0.85f, 1.0f, 1.0f), "ROOM TEMPERATURE");
    ImGui::PopFont();

    ImGui::Separator();
    ImGui::Spacing();

    char tempBuf[32];
    snprintf(tempBuf, sizeof(tempBuf), "%.1f", temperature);

    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 textSize = ImGui::CalcTextSize(tempBuf);

    ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
    ImGui::TextColored(tempColor, "%s", tempBuf);

    ImGui::End();

    ImGui::PopStyleVar(3);
}

void TemperaturePanel::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox(LANG("TemperaturePanelEnable"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    ImGui::PopStyleVar();
}
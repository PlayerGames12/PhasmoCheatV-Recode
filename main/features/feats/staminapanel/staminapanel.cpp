#include "staminapanel.h"

using namespace PhasmoCheatV::Features::Visuals;

StaminaPanel::StaminaPanel() : FeatureCore(LANG("StaminaPanel_Header"), TYPE_VISUALS) {}

void StaminaPanel::OnRender()
{
    if (!IsActive())
        return;

    if (!InGame::playerStamina)
        return;

    float currentStamina = InGame::playerStamina->Fields.CurrentStamina;

    currentStamina = std::clamp(currentStamina, 0.f, 3.f);

    constexpr float maxStamina = 3.0f;
    float staminaPercent = currentStamina / maxStamina;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(16, 16));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 10));

    constexpr ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoNav;

    ImGui::SetNextWindowSize(ImVec2(320, 100), ImGuiCond_Once);

    if (ImGui::Begin("###StaminaPanel", nullptr, flags))
    {
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
        ImGui::TextColored(
            ImVec4(0.51f, 0.25f, 0.96f, 1.00f),
            "STAMINA"
        );
        ImGui::PopFont();

        ImGui::Separator();
        ImGui::Spacing();

        char staminaText[32];
        sprintf_s(
            staminaText,
            "%.1f / %.1f",
            currentStamina,
            maxStamina
        );

        ImGui::Text("%s", staminaText);

        ImGui::PushStyleColor(
            ImGuiCol_PlotHistogram,
            ImVec4(0.25f, 0.85f, 0.35f, 1.0f)
        );

        ImGui::ProgressBar(
            staminaPercent,
            ImVec2(280.f, 24.f)
        );

        ImGui::PopStyleColor();
    }

    ImGui::End();

    ImGui::PopStyleVar(2);
}

void StaminaPanel::OnMenuRender()
{
    bool enabled = IsActive();

    if (ImGui::Checkbox(LANG("EnableStaminaPanel"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);

        if (enabled)
            OnActivate();
        else
            OnDeactivate();
    }
}
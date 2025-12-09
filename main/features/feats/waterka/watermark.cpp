#include "watermark.h"

using namespace PhasmoCheatV::Features::Visuals;

Watermark::Watermark() : FeatureCore("Watermark", TYPE_VISUALS)
{
    DECLARE_CONFIG(GetConfigManager(), "ShowSanity", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowPing", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowFPS", bool, true);

    CachedText.reserve(128);
}

void Watermark::OnRender()
{
    if (!IsActive()) return;

    const bool showPing = CONFIG_BOOL(GetConfigManager(), "ShowPing");
    const bool showSanity = CONFIG_BOOL(GetConfigManager(), "ShowSanity");
    const bool showFPS = CONFIG_BOOL(GetConfigManager(), "ShowFPS");

    CachedText = "PhasmoCheatV";

    if (showFPS)
    {
        const int fps = static_cast<int>(ImGui::GetIO().Framerate);
        CachedText.append(" | ");
        CachedText.append(std::to_string(fps));
        CachedText.append(" FPS");
    }

    if (Utils::GetCheatUptimeSeconds() > 5) // Wait cheat initialized else crash game
    {
        if (showPing && SDK::PhotonNetwork_Get_IsConnected(nullptr))
        {
                const int ping = SDK::PhotonNetwork_GetPing(nullptr);
                CachedText.append(" | ");
                CachedText.append(std::to_string(ping));
                CachedText.append(" ms");
        }
    }

    if (showSanity && InGame::mapController && InGame::mapController->Fields.GameController)
    {
        const int sanity = static_cast<int>(100.f - SDK::GameController_GetAveragePlayerInsanity(InGame::mapController->Fields.GameController, nullptr));
        CachedText.append(" | ");
        CachedText.append(std::to_string(sanity));
        CachedText.append("% Sanity");
    }

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[4]);
    const ImVec2 textSize = ImGui::CalcTextSize(CachedText.c_str());
    ImGui::PopFont();

    const float width = textSize.x + 24.0f;
    const float height = textSize.y + 10.0f;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const float padding = 10.0f;
    ImVec2 defaultPos = ImVec2(
        viewport->Size.x - padding - width,
        padding
    );
    ImGui::SetNextWindowPos(defaultPos, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

    ImGui::Begin("###WatermarkWindow", nullptr, Globals::WINDOW_FLAGS_GLOBALS);
    {
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 windowSize = ImGui::GetWindowSize();

        ImDrawList* drawList = ImGui::GetWindowDrawList();

        drawList->AddRectFilled(
            windowPos,
            ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
            IM_COL32(15, 15, 15, 180),
            12.0f
        );

        drawList->AddRect(
            windowPos,
            ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
            IM_COL32(80, 50, 120, 200),
            12.0f,
            0,
            1.5f
        );

        const ImVec2 textPos = ImVec2(
            windowPos.x + (windowSize.x - textSize.x) / 2,
            windowPos.y + (windowSize.y - textSize.y) / 2
        );

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[4]);
        drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), CachedText.c_str());
        ImGui::PopFont();
    }
    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleVar(4);
}

void Watermark::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox("Enable Watermark", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled) {
        bool showFPS = CONFIG_BOOL(GetConfigManager(), "ShowFPS");
        bool showSanity = CONFIG_BOOL(GetConfigManager(), "ShowSanity");
        bool showPing = CONFIG_BOOL(GetConfigManager(), "ShowPing");

        if (ImGui::Checkbox("Show FPS", &showFPS))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowFPS", bool, showFPS);

        if (ImGui::Checkbox("Show average sanity", &showSanity))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowSanity", bool, showSanity);

        if (ImGui::Checkbox("Show ping", &showPing))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowPing", bool, showPing);
    }

    ImGui::PopStyleVar();
}
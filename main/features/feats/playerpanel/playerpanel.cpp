#include "playerpanel.h"

using namespace PhasmoCheatV::Features::Visuals;

PlayersPanel::PlayersPanel() : FeatureCore("Players Panel", TYPE_VISUALS)
{
    DECLARE_CONFIG(GetConfigManager(), "ShowSanity", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowCurrentRoom", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowTemperature", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowLevel", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "ShowExperience", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "ShowPrestige", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "ShowHackerFlag", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "ShowAverageSanity", bool, true);
}

void PlayersPanel::OnRender()
{
    if (!IsActive())
        return;

    const auto players = Utils::GetAllPlayers();
    if (!players || players->Fields.Size == 0)
        return;

    const auto network = Utils::GetNetwork();
    if (!network || !network->Fields.NetworkPlayerSpots)
        return;

    const auto playerSpots = network->Fields.NetworkPlayerSpots->Fields.Items;
    if (!playerSpots)
        return;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(16, 16));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 12));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));
    ImGui::SetNextWindowSize(ImVec2(520, 420), ImGuiCond_Once);
    ImGui::Begin("###PlayersWindow", nullptr, Globals::WINDOW_FLAGS_GLOBALS);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::TextColored(ImVec4(0.5f, 0.8f, 1.0f, 1.0f), "PLAYERS INFO");
    ImGui::PopFont();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::BeginChild("PlayersScroll", ImVec2(0, 320), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);

    if (ImGui::BeginTable("PlayersTable", 2,
        ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_SizingFixedFit))
    {
        ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, 160);
        ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);

        auto DrawRow = [&](const char* label, const char* value) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.9f, 1.0f), "%s", label);
            ImGui::TableSetColumnIndex(1);
            ImGui::TextWrapped("%s", value);
            };

        const auto localPlayer = Utils::GetLocalPlayer();

        for (int i = 0; i < players->Fields.Size; i++)
        {
            const auto player = players->Fields.Items->Vector[i];
            if (!player) continue;

            const auto spot = playerSpots->Vector[i];
            if (!spot) continue;

            ImGui::Separator();

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TextColored(ImVec4(0.9f, 0.8f, 0.5f, 1.0f), "%s", Utils::GetPlayerName(player).c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::Text(player == localPlayer ? "(You)" : "");

            if (CONFIG_BOOL(GetConfigManager(), "ShowSanity"))
            {
                const int sanity = player->Fields.IsDead
                    ? 0
                    : static_cast<int>(100.f - Utils::GetPlayerSanity(player));
                DrawRow("Sanity", player->Fields.IsDead ? "DEAD" : std::to_string(sanity).c_str());
            }

            if (CONFIG_BOOL(GetConfigManager(), "ShowCurrentRoom"))
            {
                if (const auto levelRoom = player->Fields.LevelRoom; levelRoom && levelRoom->Fields.RoomName)
                    DrawRow("Current Room", Utils::UnityStrToSysStr(*levelRoom->Fields.RoomName).c_str());
            }

            if ((CONFIG_BOOL(GetConfigManager(), "ShowTemperature")))
            {
                if (const auto levelRoom = player->Fields.LevelRoom)
                {
                    char tempBuf[16];
                    snprintf(tempBuf, sizeof(tempBuf), "%.2f", levelRoom->Fields.temperature);
                    DrawRow("Temperature", tempBuf);
                }
            }

            if (CONFIG_BOOL(GetConfigManager(), "ShowLevel"))
                DrawRow("Level", std::to_string(spot->Fields.Level).c_str());
            if (CONFIG_BOOL(GetConfigManager(), "ShowExperience"))
                DrawRow("Experience", std::to_string(spot->Fields.Experience).c_str());
            if (CONFIG_BOOL(GetConfigManager(), "ShowPrestige"))
                DrawRow("Prestige", std::to_string(spot->Fields.Prestige).c_str());
            if (CONFIG_BOOL(GetConfigManager(), "ShowHackerFlag"))
                DrawRow("Is Hacker", spot->Fields.IsHacker ? "Yes" : "No");

            if (CONFIG_BOOL(GetConfigManager(), "ShowAverageSanity") && i == 0 && InGame::mapController && InGame::mapController->Fields.GameController)
            {
                const float avgSanity = 100.f - SDK::GameController_GetAveragePlayerInsanity(InGame::mapController->Fields.GameController, nullptr);
                char avgBuf[16];
                snprintf(avgBuf, sizeof(avgBuf), "%.0f%%", avgSanity);
                DrawRow("Average Sanity", avgBuf);
            }
        }

        ImGui::EndTable();
    }

    ImGui::EndChild();
    ImGui::End();
    ImGui::PopStyleVar(3);
}

void PlayersPanel::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox("Enable Players Panel", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled) {
        ImGui::Separator();

        bool showSanity = CONFIG_BOOL(GetConfigManager(), "ShowSanity");
        bool showRoom = CONFIG_BOOL(GetConfigManager(), "ShowCurrentRoom");
        bool showTemp = CONFIG_BOOL(GetConfigManager(), "ShowTemperature");
        bool showLevel = CONFIG_BOOL(GetConfigManager(), "ShowLevel");
        bool showExp = CONFIG_BOOL(GetConfigManager(), "ShowExperience");
        bool showPrestige = CONFIG_BOOL(GetConfigManager(), "ShowPrestige");
        bool showHacker = CONFIG_BOOL(GetConfigManager(), "ShowHackerFlag");
        bool showAverageSanity = CONFIG_BOOL(GetConfigManager(), "ShowAverageSanity");

        if (ImGui::Checkbox("Show Sanity", &showSanity))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowSanity", bool, showSanity);
        if (ImGui::Checkbox("Show Current Room", &showRoom))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowCurrentRoom", bool, showRoom);
        if (ImGui::Checkbox("Show Temperature", &showTemp))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowTemperature", bool, showTemp);
        if (ImGui::Checkbox("Show Level", &showLevel))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowLevel", bool, showLevel);
        if (ImGui::Checkbox("Show Experience", &showExp))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowExperience", bool, showExp);
        if (ImGui::Checkbox("Show Prestige", &showPrestige))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowPrestige", bool, showPrestige);
        if (ImGui::Checkbox("Show Hacker Flag", &showHacker))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowHackerFlag", bool, showHacker);
        if (ImGui::Checkbox("Show Average Sanity", &showAverageSanity))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowAverageSanity", bool, showAverageSanity);
    }

    ImGui::PopStyleVar();
}
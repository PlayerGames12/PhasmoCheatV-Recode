#include "ghostpanel.h"

using namespace PhasmoCheatV::Features::Visuals;

GhostPanel::GhostPanel() : FeatureCore("Ghost Panel", TYPE_VISUALS)
{
    DECLARE_CONFIG(GetConfigManager(), "BansheeTargetSetting", bool, false);
}

void GhostPanel::OnRender()
{
    if (!IsActive()) return;

    if (!InGame::ghostAI || !InGame::ghostAI->Fields.GhostInfo)
		return;

    const auto& ghostInfo = InGame::ghostAI->Fields.GhostInfo;
    const auto& ghostTraits = ghostInfo->Fields.GhostTraits;

    if (!ghostTraits.Name)
        return;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(16, 16));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 12));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    constexpr ImGuiWindowFlags ghostWindowFlags =
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoNav;

    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Once);
    ImGui::Begin("###GhostWindow", nullptr, ghostWindowFlags);

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::TextColored(ImVec4(0.51f, 0.25f, 0.96f, 1.00f), "GHOST PROFILE");
    ImGui::PopFont();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::BeginTable("GhostInfoPanel", 2,
        ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_SizingFixedFit))
    {
        ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, 120);
        ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);

        auto DrawRow = [&](const char* label, const char* value) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.9f, 1.0f), "%s", label);
            ImGui::TableSetColumnIndex(1);
            ImGui::TextWrapped("%s", value);
            };

        DrawRow("Name", Utils::UnityStrToSysStr(*ghostTraits.Name).c_str());
        DrawRow("Type", Utils::GhostEnumToStr(ghostTraits.GhostType_).c_str());
        DrawRow("Age", std::to_string(ghostTraits.GhostAge).c_str());
        DrawRow("State", Utils::GhostEnumToStr(InGame::ghostAI->Fields.currentState).c_str());
        DrawRow("Responds to all", (!ghostTraits.IsShy ? "Yes" : "No"));

        if (ghostTraits.GhostType_ == SDK::GhostType::Mimic)
            DrawRow("Mimic Type", Utils::GhostEnumToStr(ghostTraits.MimicType).c_str());

        if (CONFIG_BOOL(GetConfigManager(), "BansheeTargetSetting") &&
            ghostTraits.GhostType_ == SDK::GhostType::Banshee)
        {
            if (const auto& bansheeTarget = InGame::ghostAI->Fields.BansheeTarget)
                DrawRow("Target", Utils::GetPlayerName(bansheeTarget).c_str());
        }

        if (const auto& evidence = GetGhostEvidenceString(); !evidence.empty())
            DrawRow("Evidence", evidence.c_str());

        if (const auto& levelRoom = ghostInfo->Fields.favouriteRoom;
            levelRoom && levelRoom->Fields.RoomName)
        {
            DrawRow("Favorite Room", Utils::UnityStrToSysStr(*levelRoom->Fields.RoomName).c_str());
        }

        if (InGame::levelController && InGame::levelController->Fields.currentGhostRoom)
        {
            const auto ghostRoom = InGame::levelController->Fields.currentGhostRoom;
            if (ghostRoom->Fields.RoomName)
                DrawRow("Location", Utils::UnityStrToSysStr(*ghostRoom->Fields.RoomName).c_str());
        }

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.9f, 1.0f), "Status");
        ImGui::TableSetColumnIndex(1);

        if (Globals::isHunting)
            ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "HUNTING");
        else
            ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "PASSIVE");

        ImGui::EndTable();
    }

    ImGui::End();
    ImGui::PopStyleVar(3);
}

void GhostPanel::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox("Enable Ghost Panel", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled) {
        bool ghostProfile = CONFIG_BOOL(GetConfigManager(), "Enabled");
        bool bansheeTarget = CONFIG_BOOL(GetConfigManager(), "BansheeTargetSetting");

        if (ImGui::Checkbox("Show Banshee target (CRASH RISK)", &bansheeTarget))
            SET_CONFIG_VALUE(GetConfigManager(), "BansheeTargetSetting", bool, bansheeTarget);
    }

    ImGui::PopStyleVar();
}

std::string GhostPanel::GetGhostEvidenceString()
{
    const auto& ghostInfo = InGame::ghostAI->Fields.GhostInfo;
    const auto& ghostEvidenceList = ghostInfo->Fields.GhostTraits.GhostEvidenceList;

    if (!ghostEvidenceList || ghostEvidenceList->Fields.Size == 0)
        return {};

    std::string evidence;
    const auto items = ghostEvidenceList->Fields.Items->Vector;

    for (auto i = 0; i < ghostEvidenceList->Fields.Size; ++i)
    {
        if (i > 0)
            evidence += " | ";

        const std::string fullName = Utils::GhostEnumToStr(items[i]);
        if (fullName == "Ghost Writing") evidence += "Writing";
        else if (fullName == "Fingerprints") evidence += "Prints";
        else if (fullName == "Freezing Temperatures") evidence += "Freezing";
        else if (fullName == "Spirit Box") evidence += "Spirit Box";
        else evidence += fullName;
    }

    return evidence;
}

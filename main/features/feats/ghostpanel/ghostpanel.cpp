#include "ghostpanel.h"

using namespace PhasmoCheatV::Features::Visuals;

GhostPanel::GhostPanel() : FeatureCore(LANG("GhostPanel_Header"), TYPE_VISUALS)
{
    DECLARE_CONFIG(GetConfigManager(), "BansheeTargetSetting", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "IsHideSettings", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "HideName", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "HideType", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "HideAge", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "HideState", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "HideEvidence", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "HideRoom", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "HideLocation", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "HideMimicType", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "HideBansheeTarget", bool, false);
}

void GhostPanel::DrawHiddenValue(float width, float height)
{
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImDrawList* draw = ImGui::GetWindowDrawList();

    draw->AddRectFilled(
        pos,
        ImVec2(pos.x + width, pos.y + height),
        IM_COL32(0, 0, 0, 255),
        4.0f
    );

    ImGui::Dummy(ImVec2(width, height));
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
	ImGui::TextColored(ImVec4(0.51f, 0.25f, 0.96f, 1.00f), "GHOST PROFILE"); // font don't support russian and chinese language, so we use english for this title
    ImGui::PopFont();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::BeginTable("GhostInfoPanel", 2,
        ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_SizingFixedFit))
    {
        ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, 120);
        ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);

        auto DrawRow = [&](const char* label, const char* value, bool hidden) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.9f, 1.0f), "%s", label);
            ImGui::TableSetColumnIndex(1);

            if (hidden)
                DrawHiddenValue();
            else
                ImGui::TextWrapped("%s", value);
            };

        DrawRow(LANG("GhostName"), Utils::UnityStrToSysStr(*ghostTraits.Name).c_str(), CONFIG_BOOL(GetConfigManager(), "HideName"));

        DrawRow(LANG("GhostType"), Utils::GhostEnumToStr(ghostTraits.GhostType_).c_str(), CONFIG_BOOL(GetConfigManager(), "HideType"));

        DrawRow(LANG("GhostAge"), std::to_string(ghostTraits.GhostAge).c_str(), CONFIG_BOOL(GetConfigManager(), "HideAge"));
        DrawRow(LANG("GhostState"), Utils::GhostEnumToStr(InGame::ghostAI->Fields.currentState).c_str(), CONFIG_BOOL(GetConfigManager(), "HideState"));

        if (ghostTraits.GhostType_ == SDK::GhostType::Mimic)
            DrawRow(LANG("MimicType"), Utils::GhostEnumToStr(ghostTraits.MimicType).c_str(), CONFIG_BOOL(GetConfigManager(), "HideMimicType"));

        if (CONFIG_BOOL(GetConfigManager(), "BansheeTargetSetting") &&
            ghostTraits.GhostType_ == SDK::GhostType::Banshee)
        {
            if (const auto& bansheeTarget = InGame::ghostAI->Fields.BansheeTarget)
                DrawRow(LANG("BansheeTarget"), Utils::GetPlayerName(bansheeTarget).c_str(), CONFIG_BOOL(GetConfigManager(), "HideBansheeTarget"));
        }

        if (const auto& evidence = GetGhostEvidenceString(); !evidence.empty())
            DrawRow(LANG("Evidence"), evidence.c_str(), CONFIG_BOOL(GetConfigManager(), "HideEvidence"));
        if (const auto& levelRoom = ghostInfo->Fields.favouriteRoom;
            levelRoom && levelRoom->Fields.RoomName)
        {
            DrawRow(LANG("FavoriteRoom"), Utils::UnityStrToSysStr(*levelRoom->Fields.RoomName).c_str(), CONFIG_BOOL(GetConfigManager(), "HideRoom"));
        }

        if (InGame::levelController && InGame::levelController->Fields.currentGhostRoom)
        {
            const auto ghostRoom = InGame::levelController->Fields.currentGhostRoom;
            if (ghostRoom->Fields.RoomName)
                DrawRow(LANG("Location"), Utils::UnityStrToSysStr(*ghostRoom->Fields.RoomName).c_str(), CONFIG_BOOL(GetConfigManager(), "HideLocation"));
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
    if (ImGui::Checkbox(LANG("EnableGhostPanel"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled) {
        bool bansheeTarget = CONFIG_BOOL(GetConfigManager(), "BansheeTargetSetting");

        if (ImGui::Checkbox((std::string(LANG("ShowBansheeTarget")) + "##ghostPanel_banshee").c_str(), &bansheeTarget))
            SET_CONFIG_VALUE(GetConfigManager(), "BansheeTargetSetting", bool, bansheeTarget);

        bool IsHideSettings = CONFIG_BOOL(GetConfigManager(), "IsHideSettings");
        if (ImGui::Checkbox(LANG("IsHideSettingsTr"), &IsHideSettings))
            SET_CONFIG_VALUE(GetConfigManager(), "IsHideSettings", bool, IsHideSettings);

        if (IsHideSettings)
        {
            bool hideName = CONFIG_BOOL(GetConfigManager(), "HideName");
            if (ImGui::Checkbox(LANG("HideName"), &hideName))
                SET_CONFIG_VALUE(GetConfigManager(), "HideName", bool, hideName);

            bool hideType = CONFIG_BOOL(GetConfigManager(), "HideType");
            if (ImGui::Checkbox(LANG("HideType"), &hideType))
                SET_CONFIG_VALUE(GetConfigManager(), "HideType", bool, hideType);

            bool hideAge = CONFIG_BOOL(GetConfigManager(), "HideAge");
            if (ImGui::Checkbox(LANG("HideAge"), &hideAge))
                SET_CONFIG_VALUE(GetConfigManager(), "HideAge", bool, hideAge);

            bool hideState = CONFIG_BOOL(GetConfigManager(), "HideState");
            if (ImGui::Checkbox(LANG("HideState"), &hideState))
                SET_CONFIG_VALUE(GetConfigManager(), "HideState", bool, hideState);

            bool hideEvidence = CONFIG_BOOL(GetConfigManager(), "HideEvidence");
            if (ImGui::Checkbox(LANG("HideEvidence"), &hideEvidence))
                SET_CONFIG_VALUE(GetConfigManager(), "HideEvidence", bool, hideEvidence);

            bool hideRoom = CONFIG_BOOL(GetConfigManager(), "HideRoom");
            if (ImGui::Checkbox(LANG("HideRoom"), &hideRoom))
                SET_CONFIG_VALUE(GetConfigManager(), "HideRoom", bool, hideRoom);

            bool hideLocation = CONFIG_BOOL(GetConfigManager(), "HideLocation");
            if (ImGui::Checkbox(LANG("HideLocation"), &hideLocation))
                SET_CONFIG_VALUE(GetConfigManager(), "HideLocation", bool, hideLocation);

            bool hideMimic = CONFIG_BOOL(GetConfigManager(), "HideMimicType");
            if (ImGui::Checkbox(LANG("HideMimicType"), &hideMimic))
                SET_CONFIG_VALUE(GetConfigManager(), "HideMimicType", bool, hideMimic);

            bool hideTarget = CONFIG_BOOL(GetConfigManager(), "HideBansheeTarget");
            if (ImGui::Checkbox(LANG("HideBansheeTarget"), &hideTarget))
                SET_CONFIG_VALUE(GetConfigManager(), "HideBansheeTarget", bool, hideTarget);
        }
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

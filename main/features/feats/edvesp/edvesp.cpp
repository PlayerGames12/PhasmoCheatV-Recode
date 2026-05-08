#include "edvesp.h"

using namespace PhasmoCheatV::Features::Visuals;

EvidenceESP::EvidenceESP() : FeatureCore(LANG("EvidenceESP_Header"), TYPE_VISUALS)
{
    DECLARE_CONFIG(GetConfigManager(), "DNAEvidenceShow", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "CursedItemShow", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "GhostOrbShow", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "EMFShow", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "OtherEvidenceShow", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "DNAEvidenceColor", ImColor, ImColor(1.f, 1.f, 1.f, 1.f));
    DECLARE_CONFIG(GetConfigManager(), "CursedItemColor", ImColor, ImColor(1.f, 1.f, 1.f, 1.f));
    DECLARE_CONFIG(GetConfigManager(), "GhostOrbColor", ImColor, ImColor(1.f, 1.f, 1.f, 1.f));
    DECLARE_CONFIG(GetConfigManager(), "EMFColor", ImColor, ImColor(1.f, 1.f, 1.f, 1.f));
    DECLARE_CONFIG(GetConfigManager(), "OtherEvidenceColor", ImColor, ImColor(1.f, 1.f, 1.f, 1.f));
}

void EvidenceESP::OnRender()
{
    if (!IsActive() || !InGame::evidenceController)
        return;

    const bool cursedItemEnabled = CONFIG_BOOL(GetConfigManager(), "CursedItemShow");
    const bool dnaEvidenceEnabled = CONFIG_BOOL(GetConfigManager(), "DNAEvidenceShow");
    const bool emfEnabled = CONFIG_BOOL(GetConfigManager(), "EMFShow");
    const bool otherEvidenceEnabled = CONFIG_BOOL(GetConfigManager(), "OtherEvidenceShow");
    const bool ghostOrbEnabled = CONFIG_BOOL(GetConfigManager(), "GhostOrbShow");

    if (!cursedItemEnabled && !dnaEvidenceEnabled && !emfEnabled && !otherEvidenceEnabled && !ghostOrbEnabled)
        return;

    const auto evidenceList = InGame::evidenceController->Fields.EvidenceList;
    if (!evidenceList || !evidenceList->Fields.Items || evidenceList->Fields.Size <= 0)
        return;

    const auto& items = evidenceList->Fields.Items->Vector;
    const auto draw = ImGui::GetBackgroundDrawList();
    const auto cursedItemColor = CONFIG_COLOR(GetConfigManager(), "CursedItemColor");
    const auto dnaEvidenceColor = CONFIG_COLOR(GetConfigManager(), "DNAEvidenceColor");
    const auto emfColor = CONFIG_COLOR(GetConfigManager(), "EMFColor");
    const auto otherEvidenceColor = CONFIG_COLOR(GetConfigManager(), "OtherEvidenceColor");
    const auto ghostOrbColor = CONFIG_COLOR(GetConfigManager(), "GhostOrbColor");

    ImFont* normalFont = ImGui::GetFont();
    ImFont* iconFont = nullptr;

    auto& fonts = ImGui::GetIO().Fonts->Fonts;
    if (fonts.size() > 6 && fonts[6] != nullptr) {
        iconFont = fonts[6];
    }
    else {
        iconFont = normalFont;
    }

    float normalFontSize = ImGui::GetFontSize();
    float iconFontSize = normalFontSize;

    for (int i = 0; i < evidenceList->Fields.Size; i++)
    {
        if (i >= evidenceList->Fields.Size) break;

        const auto evidence = items[i];
        if (!evidence || !evidence->Fields.MediaValues)
            continue;

        const auto evidenceType = evidence->Fields.MediaValues->Fields.EvidenceType;
        const bool isCursedItem = Utils::IsCursedItem(evidenceType);
        const bool isEMF = evidenceType == SDK::EvidenceType::emfSpot;
        const bool isDNA = evidenceType == SDK::EvidenceType::DNA;
        const bool isGhostOrb = evidenceType == SDK::EvidenceType::ghostOrb;
        const bool isOther = !isCursedItem && !isEMF && !isDNA && !isGhostOrb;

        bool shouldDraw = false;
        ImColor color;

        if (isCursedItem && cursedItemEnabled) {
            shouldDraw = true;
            color = cursedItemColor;
        }
        else if (isDNA && dnaEvidenceEnabled) {
            shouldDraw = true;
            color = dnaEvidenceColor;
        }
        else if (isEMF && emfEnabled) {
            shouldDraw = true;
            color = emfColor;
        }
        else if (isGhostOrb && ghostOrbEnabled) {
            shouldDraw = true;
            color = ghostOrbColor;
        }
        else if (isOther && otherEvidenceEnabled) {
            shouldDraw = true;
            color = otherEvidenceColor;
        }

        if (!shouldDraw)
            continue;

        const auto worldPosition = Utils::GetPosVec3(reinterpret_cast<SDK::Component*>(evidence));
        SDK::Vector3 screenPosition;
        if (!Utils::WTS(worldPosition, screenPosition))
            continue;

        std::string iconLetter;
        if (isCursedItem) iconLetter = "C";
        else if (isDNA) iconLetter = "B";
        else if (isEMF) iconLetter = "V";
        else if (isGhostOrb) iconLetter = "V";
        else iconLetter = "M";

        std::string leftBracket = "[";
        std::string rightBracket = "] ";

        float leftWidth = normalFont->CalcTextSizeA(normalFontSize, FLT_MAX, 0.0f, leftBracket.c_str()).x;
        float iconWidth = iconFont->CalcTextSizeA(iconFontSize, FLT_MAX, 0.0f, iconLetter.c_str()).x;
        float rightWidth = normalFont->CalcTextSizeA(normalFontSize, FLT_MAX, 0.0f, rightBracket.c_str()).x;

        draw->AddText(normalFont, normalFontSize, ImVec2(screenPosition.X, screenPosition.Y), color, leftBracket.c_str());
        draw->AddText(iconFont, iconFontSize, ImVec2(screenPosition.X + leftWidth, screenPosition.Y), color, iconLetter.c_str());
        draw->AddText(normalFont, normalFontSize, ImVec2(screenPosition.X + leftWidth + iconWidth, screenPosition.Y), color, rightBracket.c_str());

        std::string displayText = Utils::GhostEnumToStr(evidenceType);
        if (!displayText.empty()) {
            draw->AddText(normalFont, normalFontSize,
                ImVec2(screenPosition.X + leftWidth + iconWidth + rightWidth, screenPosition.Y),
                color, displayText.c_str());
        }
    }
}

void EvidenceESP::OnMenuRender()
{
    constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

    auto MakeLabel = [](const char* code, const char* id) -> std::string
        {
            return std::string(LANG(code)) + "##" + id;
        };

    bool enabled = IsActive();
    bool cursedItemEnabled = CONFIG_BOOL(GetConfigManager(), "CursedItemShow");
    bool dnaEvidenceEnabled = CONFIG_BOOL(GetConfigManager(), "DNAEvidenceShow");
    bool ghostOrbEnabled = CONFIG_BOOL(GetConfigManager(), "GhostOrbShow");
    bool emfEnabled = CONFIG_BOOL(GetConfigManager(), "EMFShow");
    bool otherEvidenceEnabled = CONFIG_BOOL(GetConfigManager(), "OtherEvidenceShow");

    ImColor cursedItemColor = CONFIG_COLOR(GetConfigManager(), "CursedItemColor");
    ImColor dnaEvidenceColor = CONFIG_COLOR(GetConfigManager(), "DNAEvidenceColor");
    ImColor ghostOrbColor = CONFIG_COLOR(GetConfigManager(), "GhostOrbColor");
    ImColor emfColor = CONFIG_COLOR(GetConfigManager(), "EMFColor");
    ImColor otherEvidenceColor = CONFIG_COLOR(GetConfigManager(), "OtherEvidenceColor");

    if (ImGui::Checkbox(LANG("EnableEvidenceESP"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        enabled ? OnActivate() : OnDeactivate();
    }

    if (!enabled)
        return;

    if (ImGui::Checkbox(LANG("CursedItem"), &cursedItemEnabled))
        SET_CONFIG_VALUE(GetConfigManager(), "CursedItemShow", bool, cursedItemEnabled);

    ImGui::SameLine();
    if (ImGui::ColorEdit4(
        MakeLabel("Color", "cursed").c_str(),
        reinterpret_cast<float*>(&cursedItemColor.Value),
        colorEditFlags))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "CursedItemColor", ImColor, cursedItemColor);
    }

    if (ImGui::Checkbox(LANG("DNAEvidence"), &dnaEvidenceEnabled))
        SET_CONFIG_VALUE(GetConfigManager(), "DNAEvidenceShow", bool, dnaEvidenceEnabled);

    ImGui::SameLine();
    if (ImGui::ColorEdit4(
        MakeLabel("Color", "dna").c_str(),
        reinterpret_cast<float*>(&dnaEvidenceColor.Value),
        colorEditFlags))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "DNAEvidenceColor", ImColor, dnaEvidenceColor);
    }

    if (ImGui::Checkbox(LANG("EMFSpots"), &emfEnabled))
        SET_CONFIG_VALUE(GetConfigManager(), "EMFShow", bool, emfEnabled);

    ImGui::SameLine();
    if (ImGui::ColorEdit4(
        MakeLabel("Color", "emf").c_str(),
        reinterpret_cast<float*>(&emfColor.Value),
        colorEditFlags))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "EMFColor", ImColor, emfColor);
    }

    if (ImGui::Checkbox(LANG("GhostOrb"), &ghostOrbEnabled))
        SET_CONFIG_VALUE(GetConfigManager(), "GhostOrbShow", bool, ghostOrbEnabled);

    ImGui::SameLine();
    if (ImGui::ColorEdit4(
        MakeLabel("Color", "ghostOrb").c_str(),
        reinterpret_cast<float*>(&ghostOrbColor.Value),
        colorEditFlags))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "GhostOrbColor", ImColor, ghostOrbColor);
    }

    if (ImGui::Checkbox(LANG("OtherEvidence"), &otherEvidenceEnabled))
        SET_CONFIG_VALUE(GetConfigManager(), "OtherEvidenceShow", bool, otherEvidenceEnabled);

    ImGui::SameLine();
    if (ImGui::ColorEdit4(
        MakeLabel("Color", "other").c_str(),
        reinterpret_cast<float*>(&otherEvidenceColor.Value),
        colorEditFlags))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "OtherEvidenceColor", ImColor, otherEvidenceColor);
    }
}

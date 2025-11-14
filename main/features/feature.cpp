#include "feature.h"
#include <algorithm>

#include "feats/waterka/watermark.h"
#include "../config/configs_manager.h"

using namespace PhasmoCheatV;
using namespace Features::Visuals;
using namespace Features::Configs;

const char* PhasmoCheatV::GetFeatureTypeName(const FeatureType type)
{
    switch (type)
    {
    case TYPE_NONE: return "None";
    case TYPE_VISUALS: return "V";
    case TYPE_PLAYERS: return "P";
    case TYPE_GHOST: return "G";
    case TYPE_CURSED: return "C";
    case TYPE_MISC: return "M";
    case TYPE_MOVEMENT: return "L";
    case TYPE_CONFIGS: return "K";
    case TYPE_DIFFICULTY: return "D";
    default: return "U";
    }
}

FeatureHandler::FeatureHandler() : CurrentType(TYPE_NONE)
{
    FeatureRegistry = std::unordered_map<std::string, std::unique_ptr<FeatureCore>>();

    ADD_FEATURE(this, Watermark);
    ADD_FEATURE(this, ConfigsManager);

    MainFeatureHandler = this;
}

FeatureHandler::~FeatureHandler()
{
    MainFeatureHandler = nullptr;
}

void FeatureHandler::RegisterFeature(const std::string_view name, std::unique_ptr<FeatureCore> feature)
{
    FeatureRegistry.emplace(std::string(name), std::move(feature));
}

FeatureCore* FeatureHandler::FindFeature(const std::string_view name) const
{
    if (const auto it = FeatureRegistry.find(std::string(name)); it != FeatureRegistry.end())
        return it->second.get();
    return nullptr;
}

void FeatureHandler::RenderAll() const
{
    for (const auto& [name, feature] : FeatureRegistry)
    {
        if (feature->IsActive())
        {
            feature->OnRender();
        }
    }
}

void FeatureHandler::ShowTypeSelector()
{
    constexpr std::array<FeatureType, 8> TYPES = {
        TYPE_VISUALS, TYPE_PLAYERS, TYPE_GHOST, TYPE_CURSED,
        TYPE_MOVEMENT, TYPE_MISC, TYPE_CONFIGS, TYPE_DIFFICULTY
    };

    const float width = ImGui::GetContentRegionAvail().x;
    const float btnSize = (width - 20.0f * 2) / 3.0f;
    const ImVec2 size(btnSize, btnSize);

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(12, 12));

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 50);
    ImGui::BeginGroup();

    int count = 0;
    for (FeatureType type : TYPES)
    {
        if (count > 0 && count % 3 != 0)
            ImGui::SameLine();

        const char* icon = GetFeatureTypeName(type);
        const char* label = "Unknown";

        switch (type)
        {
        case TYPE_VISUALS: label = "Visuals"; break;
        case TYPE_PLAYERS: label = "Players"; break;
        case TYPE_GHOST: label = "Ghost"; break;
        case TYPE_CURSED: label = "Cursed"; break;
        case TYPE_MOVEMENT: label = "Movement"; break;
        case TYPE_MISC: label = "Misc"; break;
        case TYPE_CONFIGS: label = "Configs"; break;
        case TYPE_DIFFICULTY: label = "Difficulty"; break;
        }

        if (ImGui::Button(("##btn_" + std::to_string(count)).c_str(), size))
            CurrentType = type;

        const ImVec2 pos = ImGui::GetItemRectMin();
        const ImVec2 itemSize = ImGui::GetItemRectSize();
        const ImVec2 center(pos.x + itemSize.x * 0.5f, pos.y + itemSize.y * 0.5f);
        auto* draw = ImGui::GetWindowDrawList();

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
        ImVec2 iconText = ImGui::CalcTextSize(icon);
        draw->AddText(ImVec2(center.x - iconText.x * 0.5f, center.y - iconText.y * 0.5f - 6.0f),
            IM_COL32_WHITE, icon);
        ImGui::PopFont();

        ImVec2 textSize = ImGui::CalcTextSize(label);
        draw->AddText(ImVec2(center.x - textSize.x * 0.5f, pos.y + itemSize.y - textSize.y - 6.0f),
            IM_COL32_WHITE, label);

        count++;
    }

    ImGui::EndGroup();
    ImGui::PopStyleVar(2);
}

void FeatureHandler::ShowFeaturesByType()
{
    if (ImGui::Button("Back", ImVec2(80, 30)))
    {
        CurrentType = TYPE_NONE;
        return;
    }

    ImGui::SameLine();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::BeginChild("Features", ImVec2(0, 0), true);

    for (const auto& [name, feature] : FeatureRegistry)
    {
        if (feature->GetFeatureType() == CurrentType && feature->ShowInMenu)
        {
            ImGui::PushID(name.c_str());
            feature->OnMenuRender();
            ImGui::Separator();
            ImGui::PopID();
        }
    }

    ImGui::EndChild();
}

void FeatureHandler::RenderMenu()
{
    if (CurrentType == TYPE_NONE)
    {
        ShowTypeSelector();
    }
    else
    {
        ShowFeaturesByType();
    }
}
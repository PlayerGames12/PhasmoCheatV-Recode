#include "feature.h"
#include "features_includes.h"

using namespace PhasmoCheatV;
using namespace Features::Visuals;
using namespace Features::Players;
using namespace Features::Configs;
using namespace Features::Ghost;
using namespace Features::Cursed;
using namespace Features::Movement;
using namespace Features::Misc;
using namespace Features::Difficulty;
using namespace Features::Map;

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
    case TYPE_MAP: return "m";
    default: return "U";
    }
}

const char* PhasmoCheatV::GetFeatureTypeFullName(const FeatureType type)
{
    switch (type)
    {
    case TYPE_NONE: return "None";
    case TYPE_VISUALS: return "Visuals";
    case TYPE_PLAYERS: return "Players";
    case TYPE_GHOST: return "Ghost";
    case TYPE_CURSED: return "Cursed items";
    case TYPE_MISC: return "Misc";
    case TYPE_MOVEMENT: return "Movement";
    case TYPE_CONFIGS: return "Configs";
    case TYPE_DIFFICULTY: return "Difficulty";
    case TYPE_MAP: return "Map";
    default: return "Unkown";
    }
}

FeatureHandler::FeatureHandler() : CurrentType(TYPE_NONE)
{
    FeatureRegistry = std::vector<std::pair<std::string, std::unique_ptr<FeatureCore>>>();

    ADD_FEATURE(this, Watermark);
    ADD_FEATURE(this, GhostPanel);
    ADD_FEATURE(this, GhostESP);
    ADD_FEATURE(this, FuseBoxESP);
    ADD_FEATURE(this, EvidenceESP);
    ADD_FEATURE(this, Fullbright);
    ADD_FEATURE(this, PlayersPanel);
    ADD_FEATURE(this, StatsPanel);
    ADD_FEATURE(this, PlayerESP);
    ADD_FEATURE(this, ActivityMonitor);
    ADD_FEATURE(this, ConfigsManager);
    ADD_FEATURE(this, GodMode);
    ADD_FEATURE(this, Pickup);
    ADD_FEATURE(this, FoVEditor);
    ADD_FEATURE(this, CustomLookLimits);
    ADD_FEATURE(this, CustomName);
    ADD_FEATURE(this, PlayerModifier);
    ADD_FEATURE(this, GhostModifier);
    ADD_FEATURE(this, GhostInteractor);
    ADD_FEATURE(this, GhostDesigner);
    ADD_FEATURE(this, CursedItemsControll);
    ADD_FEATURE(this, InfinityStamina);
    ADD_FEATURE(this, NoClip);
    ADD_FEATURE(this, CustomSpeed);
    ADD_FEATURE(this, Teleport);
    ADD_FEATURE(this, AntiKick);
    ADD_FEATURE(this, ExitVanOne);
    ADD_FEATURE(this, RewardModifier);
    ADD_FEATURE(this, ShopModifier);
    ADD_FEATURE(this, DifficultyModifier);
    ADD_FEATURE(this, MapModifier);
	ADD_FEATURE(this, DoorModifier);
    ADD_FEATURE(this, GrabKeys);
    ADD_FEATURE(this, SaltModifier);

    MainFeatureHandler = this;
}

FeatureHandler::~FeatureHandler()
{
    MainFeatureHandler = nullptr;
}

void FeatureHandler::RegisterFeature(const std::string_view name, std::unique_ptr<FeatureCore> feature)
{
    FeatureRegistry.emplace_back(std::string(name), std::move(feature));
}

FeatureCore* FeatureHandler::FindFeature(const std::string_view name) const
{
    for (const auto& [featureName, feature] : FeatureRegistry)
    {
        if (featureName == name)
            return feature.get();
    }
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

bool FeatureHandler::FeatureMatchesSearch(const std::string& featureName, const std::string& query) const
{
    if (query.empty()) return false;

    auto it = std::search(
        featureName.begin(), featureName.end(),
        query.begin(), query.end(),
        [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
    );

    return (it != featureName.end());
}

void FeatureHandler::ShowTypeSelector()
{
    constexpr std::array<FeatureType, 9> TYPES = {
        TYPE_VISUALS, TYPE_PLAYERS, TYPE_GHOST, TYPE_CURSED,
        TYPE_MOVEMENT, TYPE_MISC, TYPE_CONFIGS, TYPE_DIFFICULTY, TYPE_MAP
    };

    const float width = ImGui::GetContentRegionAvail().x;
    const float btnSize = (width - 20.0f * 2) / 3.0f;
    const ImVec2 size(btnSize, btnSize);

    ImGui::SetNextItemWidth(width - 20.f);
    ImGui::InputTextWithHint("##SearchFeatures", "Search features...", SearchBuffer, sizeof(SearchBuffer));
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (SearchBuffer[0] != '\0')
    {
        std::string query = SearchBuffer;
        bool foundAny = false;

        ImGui::BeginChild("SearchResults", ImVec2(0, 0), true);

        for (const auto& [name, feature] : FeatureRegistry)
        {
            if (FeatureMatchesSearch(name, query) || FeatureMatchesSearch(feature->GetFeatureTitle(), query))
            {
                if (feature->ShowInMenu)
                {
                    ImGui::PushID(name.c_str());

                    ImGui::TextDisabled("[%s]", GetFeatureTypeFullName(feature->GetFeatureType()));
                    ImGui::SameLine();
                    ImGui::SeparatorText(feature->GetFeatureTitle().c_str());

                    feature->OnMenuRender();
                    ImGui::Spacing();
                    ImGui::PopID();

                    foundAny = true;
                }
            }
        }

        if (!foundAny)
        {
            ImGui::TextDisabled("No features found matching '%s'", SearchBuffer);
        }

        ImGui::EndChild();
        return;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(12, 12));
    ImGui::Spacing();
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
        case TYPE_MAP: label = "Map"; break;
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
    const char* categoryName = "Unknown";
    switch (CurrentType)
    {
    case TYPE_VISUALS: categoryName = "Visuals"; break;
    case TYPE_PLAYERS: categoryName = "Players"; break;
    case TYPE_GHOST: categoryName = "Ghost"; break;
    case TYPE_CURSED: categoryName = "Cursed"; break;
    case TYPE_MOVEMENT: categoryName = "Movement"; break;
    case TYPE_MISC: categoryName = "Misc"; break;
    case TYPE_CONFIGS: categoryName = "Configs"; break;
    case TYPE_DIFFICULTY: categoryName = "Difficulty"; break;
    case TYPE_MAP: categoryName = "Map"; break;
    }
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[7]);
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%s Features", categoryName);
    ImGui::PopFont();
    ImGui::Separator();
    ImGui::Spacing();
    if (ImGui::Button("<- Back to Categories", ImVec2(150, 30)))
    {
        CurrentType = TYPE_NONE;
        return;
    }
    ImGui::Spacing();
    ImGui::BeginChild("Features", ImVec2(0, 0), true);

    for (const auto& [name, feature] : FeatureRegistry)
    {
        if (feature->GetFeatureType() == CurrentType && feature->ShowInMenu)
        {
            ImGui::PushID(name.c_str());
            ImGui::SeparatorText(feature->GetFeatureTitle().c_str());
            feature->OnMenuRender();
            ImGui::Spacing();
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
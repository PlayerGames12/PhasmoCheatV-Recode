#include "rewardmodifier.h"

using namespace PhasmoCheatV::Features::Misc;

RewardModifier::RewardModifier() : FeatureCore("Reward Modifier", TYPE_MISC)
{
    DECLARE_CONFIG(GetConfigManager(), "InvestigationBonus", int, 1000);
    DECLARE_CONFIG(GetConfigManager(), "InvestigationBonusEnabled", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "PerfectGame", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "MediaBonusEnabled", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "MediaBonusValue", int, 0);
    DECLARE_CONFIG(GetConfigManager(), "AutoCompleteObjectives", bool, false);
}

void RewardModifier::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox("Enable Reward Modifier", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled)
    {
        bool perfectGame = CONFIG_BOOL(GetConfigManager(), "PerfectGame");
        if (ImGui::Checkbox("Always Perfect Game##rewardmod", &perfectGame))
            SET_CONFIG_VALUE(GetConfigManager(), "PerfectGame", bool, perfectGame);

        bool autoCompleteObjectives = CONFIG_BOOL(GetConfigManager(), "AutoCompleteObjectives");
        if (ImGui::Checkbox("Auto Complete Objectives##rewardmod", &autoCompleteObjectives))
            SET_CONFIG_VALUE(GetConfigManager(), "AutoCompleteObjectives", bool, autoCompleteObjectives);

        bool customBonus = CONFIG_BOOL(GetConfigManager(), "InvestigationBonusEnabled");
        if (ImGui::Checkbox("Enable Custom Investigation Bonus##rewardmod", &customBonus))
            SET_CONFIG_VALUE(GetConfigManager(), "InvestigationBonusEnabled", bool, customBonus);

        if (customBonus)
        {
            int investigationBonus = CONFIG_INT(GetConfigManager(), "InvestigationBonus");
            if (ImGui::InputInt("Investigation Bonus##rewardmod", &investigationBonus))
            {
                investigationBonus = std::max<int>(0, investigationBonus);
                SET_CONFIG_VALUE(GetConfigManager(), "InvestigationBonus", int, investigationBonus);
            }
        }

        bool mediaBonusEnabled = CONFIG_BOOL(GetConfigManager(), "MediaBonusEnabled");
        if (ImGui::Checkbox("Enable Media Bonus##rewardmod", &mediaBonusEnabled))
            SET_CONFIG_VALUE(GetConfigManager(), "MediaBonusEnabled", bool, mediaBonusEnabled);

        if (mediaBonusEnabled)
        {
            int mediaBonus = CONFIG_INT(GetConfigManager(), "MediaBonusValue");
            if (ImGui::InputInt("Media Bonus Value##rewardmod", &mediaBonus))
            {
                mediaBonus = std::max<int>(0, mediaBonus);
                SET_CONFIG_VALUE(GetConfigManager(), "MediaBonusValue", int, mediaBonus);
            }
        }
    }

    ImGui::PopStyleVar();
}

int32_t RewardModifier::RewardModifierMainBonus(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo)
{
    if (!IsActive() || !CONFIG_BOOL(GetConfigManager(), "InvestigationBonusEnabled"))
        return SDK::LevelValues_GetInvestigationBonusReward(levelValues, methodInfo);

    return CONFIG_INT(GetConfigManager(), "InvestigationBonus");
}

bool RewardModifier::RewardModifierMainPrefGame(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo)
{
    if (!IsActive() || !CONFIG_BOOL(GetConfigManager(), "PerfectGame"))
        return SDK::LevelValues_IsPerfectGame(levelValues, methodInfo);

    return true;
}

int32_t RewardModifier::RewardModifierMainMediaBonus(SDK::MediaValues* mediaValues, SDK::EvidenceQualityType qualityType, SDK::TierList mediaTier, SDK::MethodInfo* methodInfo)
{
    if (!IsActive() || !CONFIG_BOOL(GetConfigManager(), "MediaBonusEnabled"))
        return SDK::MediaValues_GetRewardAmount(mediaValues, qualityType, mediaTier, methodInfo);

    int32_t originalValue = SDK::MediaValues_GetRewardAmount(mediaValues, qualityType, mediaTier, methodInfo);
    int32_t bonus = CONFIG_INT(GetConfigManager(), "MediaBonusValue");
    
    return originalValue + bonus;
}

void RewardModifier::RewardModifierObjectives(SDK::ObjectiveManager* om)
{
    if (!IsActive() || !CONFIG_BOOL(GetConfigManager(), "AutoCompleteObjectives"))
        return;

    const std::vector<SDK::ObjectivesType> allObjectives = {
        SDK::ObjectivesType::BlowoutCandle,
        SDK::ObjectivesType::DetectParabolicSound,
        SDK::ObjectivesType::EMFGhost,
        SDK::ObjectivesType::EscapeHunt,
        SDK::ObjectivesType::GhostPhoto,
        SDK::ObjectivesType::IdentifyGhost,
        SDK::ObjectivesType::MotionSensorGhost,
        SDK::ObjectivesType::PreventHunt,
        SDK::ObjectivesType::SanityBelow25,
        SDK::ObjectivesType::SmudgeGhost,
        SDK::ObjectivesType::SmudgeHunt,
        SDK::ObjectivesType::WitnessEvent,
        SDK::ObjectivesType::DnaEvidence,
        SDK::ObjectivesType::CompleteInTimeLimit,
        SDK::ObjectivesType::GhostVideo,
        SDK::ObjectivesType::UniquePhotos,
        SDK::ObjectivesType::UniqueVideos,
        SDK::ObjectivesType::UniqueSounds
    };

    for (auto obj : allObjectives)
    {
        SDK::ObjectiveManager_CompleteObjectiveSynced(om, obj, nullptr);
    }
}
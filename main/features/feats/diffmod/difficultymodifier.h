#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Difficulty
{
    class DifficultyModifier final : public FeatureCore
    {
    public:
        DifficultyModifier();
        ~DifficultyModifier() override = default;

        void OnActivate() override {}
        void OnDeactivate() override {}
        void OnRender() override {}
        void OnMenuRender() override;
        void DifficultyModifierApply();

    private:
        void AddSettingToModify(int settingIndex);
        void RemoveSetting(int index);
        void RenderSettingEditor(int index);
        const char* GetConfigKey(int settingIndex) const;

        std::vector<int> m_selectedSettings;
        std::vector<std::pair<std::string, int>> m_availableSettings = {
            {"Required Level", 0},
            {"Sanity Pill Restoration", 1},
            {"Starting Sanity", 2},
            {"Sanity Drain", 3},
            {"Sprinting", 4},
            {"Flashlights", 5},
            {"Lose Items On Death", 6},
            {"Player Speed", 7},
            {"Evidence Given", 8},
            {"Changing Favourite Room", 9},
            {"Interaction Amount", 10},
            {"Event Frequency", 11},
            {"Hunt Duration", 12},
            {"Grace Period", 13},
            {"Fingerprint Chance", 14},
            {"Fingerprint Duration", 15},
            {"Friendly Ghost", 16},
            {"Kills Extend Hunt", 17},
            {"Roaming Frequency", 18},
            {"Ghost Speed", 19},
            {"Setup Time", 20},
            {"Selected Weather", 21},
            {"Doors Open", 22},
            {"Hiding Places", 23},
            {"Sanity Monitor", 24},
            {"Activity Monitor", 25},
            {"FuseBox Visible", 26},
            {"FuseBox Start Power", 27}
        };
    };
}
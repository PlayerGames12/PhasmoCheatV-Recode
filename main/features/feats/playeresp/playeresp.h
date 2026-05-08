#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
    class PlayerESP final : public FeatureCore
    {
    public:
        PlayerESP();
        ~PlayerESP() override = default;

        void OnActivate() override {}
        void OnDeactivate() override {}
        void OnRender() override;
        void OnMenuRender() override;

    private:
        void DrawSkeleton(const std::unordered_map<SDK::HumanBodyBones, SDK::Vector3>& screenBonePositions, const ImColor& color, float thickness);
        bool GetBonePositions(const SDK::Player* player, std::unordered_map<SDK::HumanBodyBones, SDK::Vector3>& bonePositions, bool includeAllBones);
        bool CalculateBoundingBox(const std::unordered_map<SDK::HumanBodyBones, SDK::Vector3>& screenBonePositions, ImVec2& boxMin, ImVec2& boxMax);
        static const std::vector<std::pair<SDK::HumanBodyBones, SDK::HumanBodyBones>> SKELETON_CONNECTIONS;
        static const std::vector<SDK::HumanBodyBones> MAIN_BONES;
        static const std::vector<SDK::HumanBodyBones> ESSENTIAL_BONES;
    };
}
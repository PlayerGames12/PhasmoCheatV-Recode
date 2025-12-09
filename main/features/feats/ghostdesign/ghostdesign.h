#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Ghost
{
    class GhostDesigner final : public FeatureCore
    {
    public:
        GhostDesigner();
        ~GhostDesigner() override = default;

        void OnActivate() override {}
        void OnDeactivate() override {}
        void OnRender() override {}
        void OnMenuRender() override;
        void ApplyGhostSettings(int& ghostType, int& ghostAge, bool& isShy);
        void ApplyGhostEvidence(int* evidence);
    };
}
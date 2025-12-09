#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
    class EvidenceESP final : public FeatureCore
    {
    public:
        explicit EvidenceESP();
        ~EvidenceESP() override = default;

        void OnActivate() override {}
        void OnDeactivate() override {}

        void OnRender() override;
        void OnMenuRender() override;
    };
}
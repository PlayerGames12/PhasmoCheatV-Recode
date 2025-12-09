#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Players
{
    class PlayerModifier final : public FeatureCore
    {
    public:
        explicit PlayerModifier();
        ~PlayerModifier() override = default;

        void OnActivate() override {}
        void OnDeactivate() override {}
        void OnRender() override {}
        void OnMenuRender() override;
    };
}
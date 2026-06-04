#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Auto
{
    class AutoPickupBone final : public FeatureCore
    {
    public:
        explicit AutoPickupBone();
        ~AutoPickupBone() override = default;

        void OnActivate() override {}
        void OnDeactivate() override {}
        void OnRender() override {}
        void OnMenuRender() override;
    };
}
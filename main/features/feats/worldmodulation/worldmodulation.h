#pragma once
#include "../../feature.h"
#include <vector> // code by @softvoidds
#include <string>

namespace PhasmoCheatV::Features::Visuals
{
    class WorldModulation final : public FeatureCore
    {
    public:
        WorldModulation();
        ~WorldModulation() override = default;

        void OnActivate() override;
        void OnDeactivate() override;
        void OnRender() override;
        void OnMenuRender() override;

    private:
        void ApplyModulation();
        void RestoreOriginalMaterials() {}

        struct CachedConfig
        {
            bool affectMaterials = true;
            SDK::Color color{ 1,1,1,1 };
        } Cache;
    };
}
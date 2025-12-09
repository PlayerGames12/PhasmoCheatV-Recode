#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
    class PlayersPanel final : public FeatureCore
    {
    public:
        PlayersPanel();
        ~PlayersPanel() override = default;

        void OnActivate() override {}
        void OnDeactivate() override {}

        void OnRender() override;
        void OnMenuRender() override;
    };
}

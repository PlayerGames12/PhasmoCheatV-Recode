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

    private:
        void ChangeSanityPlayer(bool isLocal, SDK::Player* player, float sanity);
        void RevivePlayer(SDK::Player* player);
        void SetBansheeTarget(SDK::Player* player);
    };
}
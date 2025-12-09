#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Map
{
    class DoorModifier final : public FeatureCore
    {
    public:
        explicit DoorModifier();
        ~DoorModifier() override = default;

        void OnActivate() override {}
        void OnDeactivate() override {}
        void OnRender() override {}
        void OnMenuRender() override;
        void DoorModifierMain();

    private:
        enum class DoorAction
        {
            ToggleInteraction,
            ToggleLock,
            TeleportToPlayer,
            DisableAll,
            EnableAll
        };

        void ProcessDoorAction(DoorAction action, bool enable = false);
        void ProcessDoorArray(SDK::DoorArray* doorArray, DoorAction action, bool enable);
    };
}
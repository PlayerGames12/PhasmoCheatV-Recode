#include "ghostinter.h"

using namespace PhasmoCheatV::Features::Ghost;

GhostInteractor::GhostInteractor() : FeatureCore(LANG("GhostInteractionControl_Header"), TYPE_GHOST) {}

static bool CanTrigger()
{
    if (!InGame::ghostAI)
    {
        NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
        return false;
    }

    if (!Utils::IsLocalMasterClient())
    {
        NOTIFY_ERROR_QUICK(LANG("NeedMustBeHost"));
        return false;
    }

    return true;
}

void GhostInteractor::OnMenuRender()
{
    struct BtnDef
    {
        const char* code;
        bool* flag;
    };

    BtnDef buttons[] = {
        { "TriggerAbility",         &TriggerAbility     },
        { "GenericInteraction",     &TriggerGeneric     },
        { "RandomLightSwitch",      &TriggerLight       },
        { "RandomDoorInteraction",  &TriggerDoor        },
        { "RandomPropInteraction",  &TriggerProp        },
        { "StandardInteraction",    &TriggerStandard    },
        { "TwinInteraction",        &TriggerTwin        },
    };

    for (size_t i = 0; i < std::size(buttons); i++)
    {
        BButton(
            buttons[i].code,
            "ghostInteractor_" + std::to_string(i),
            ([buttons, i]()
                {
                    if (CanTrigger())
                        *buttons[i].flag = true;
                })
        );

        if (i % 2 == 0 &&
            i + 1 < std::size(buttons))
            ImGui::SameLine();
    }
}

void GhostInteractor::GhostInteractorMain()
{
    auto ai = InGame::ghostAI;
    if (!ai)
        return;

    auto activity = ai->Fields.GhostActivity;
    if (!activity)
        return;

    if (TriggerAbility)
    {
        SDK::GhostActivity_GhostAbility(activity, nullptr);
        TriggerAbility = false;
    }

    if (TriggerGeneric)
    {
        SDK::GhostActivity_TryInteract(activity, nullptr);
        TriggerGeneric = false;
    }

    if (TriggerLight)
    {
        SDK::GhostActivity_InteractWithRandomLightSwitch(activity, false, nullptr);
        TriggerLight = false;
    }

    if (TriggerDoor)
    {
        SDK::GhostActivity_InteractWithARandomDoor(activity, nullptr);
        TriggerDoor = false;
    }

    if (TriggerProp)
    {
        SDK::GhostActivity_InteractWithARandomProp(activity, true, nullptr);
        TriggerProp = false;
    }

    if (TriggerStandard)
    {
        SDK::GhostActivity_NormalInteraction(activity, true, nullptr);
        TriggerStandard = false;
    }

    if (TriggerTwin)
    {
        SDK::GhostActivity_TwinInteraction(activity, true, nullptr);
        TriggerTwin = false;
    }
}

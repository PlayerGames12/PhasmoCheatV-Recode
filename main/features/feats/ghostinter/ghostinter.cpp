#include "ghostinter.h"

using namespace PhasmoCheatV::Features::Ghost;

GhostInteractor::GhostInteractor() : FeatureCore("Ghost Interaction Control", TYPE_GHOST) {}

static bool CanTrigger()
{
    if (!InGame::ghostAI)
    {
        NOTIFY_ERROR_QUICK("You need to be in the game.");
        return false;
    }

    if (!Utils::IsLocalMasterClient())
    {
        NOTIFY_ERROR_QUICK("You must be host to use this feature.");
        return false;
    }

    return true;
}

void GhostInteractor::OnMenuRender()
{
    struct BtnDef
    {
        const char* label;
        bool* flag;
    };

    BtnDef buttons[] = {
        { "Trigger ability",         &TriggerAbility     },
        { "Generic interaction",     &TriggerGeneric     },
        { "Random light switch",     &TriggerLight       },
        { "Random door interaction", &TriggerDoor        },
        { "Random prop interaction", &TriggerProp        },
        { "Standard interaction",    &TriggerStandard    },
        { "Twin interaction",        &TriggerTwin        },
    };

    for (size_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
    {
        if (ImGui::Button(buttons[i].label, ImVec2(220, 0)))
        {
            if (CanTrigger())
                *buttons[i].flag = true;
        }

        if (i % 2 == 0 && i + 1 < sizeof(buttons) / sizeof(buttons[0]))
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

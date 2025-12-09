#include "doormodifier.h"

using namespace PhasmoCheatV::Features::Map;

DoorModifier::DoorModifier() : FeatureCore("Door Modifier", TYPE_MAP)
{
    DECLARE_CONFIG(GetConfigManager(), "DisableInteraction", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "LockDoors", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "TeleportToPlayer", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "DisableAllDoors", bool, false);
}

void DoorModifier::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox("Enable Door Modifier", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled)
    {
        ImGui::Separator();

        if (ImGui::Button("Disable Door Interaction"))
            ProcessDoorAction(DoorAction::ToggleInteraction, false);
        ImGui::SameLine();
        if (ImGui::Button("Enable Door Interaction"))
            ProcessDoorAction(DoorAction::ToggleInteraction, true);

        if (ImGui::Button("Teleport Doors To Player"))
            ProcessDoorAction(DoorAction::TeleportToPlayer);

        if (ImGui::Button("Disable All Doors"))
            ProcessDoorAction(DoorAction::DisableAll);
        ImGui::SameLine();
        if (ImGui::Button("Enable All Doors"))
            ProcessDoorAction(DoorAction::EnableAll);
    }

    ImGui::PopStyleVar();
}

void DoorModifier::ProcessDoorAction(DoorAction action, bool enable)
{
    if (!InGame::levelController)
    {
        NOTIFY_ERROR_QUICK("You need to be in the game.");
        return;
    }

    auto& levelFields = InGame::levelController->Fields;
    SDK::DoorArray* doorArrays[2] = {
        reinterpret_cast<SDK::DoorArray*>(levelFields.doors),
        reinterpret_cast<SDK::DoorArray*>(levelFields.exitDoors)
    };

    uint32_t affectedDoors = 0;

    for (int arrIdx = 0; arrIdx < 2; arrIdx++)
    {
        if (doorArrays[arrIdx])
        {
            ProcessDoorArray(doorArrays[arrIdx], action, enable);

            for (uint32_t i = 0; i < 65535; i++)
            {
                if (doorArrays[arrIdx]->Vector[i] == nullptr)
                    break;
                affectedDoors++;
            }
        }
    }

    switch (action)
    {
    case DoorAction::ToggleInteraction:
        NOTIFY_INFO_QUICK(enable ? "Door interaction enabled" : "Door interaction disabled");
        break;
    case DoorAction::TeleportToPlayer:
        NOTIFY_INFO_QUICK("Doors teleported to player");
        break;
    case DoorAction::DisableAll:
        NOTIFY_INFO_QUICK("All doors disabled");
        break;
    case DoorAction::EnableAll:
        NOTIFY_INFO_QUICK("All doors enabled");
        break;
    }
}

void DoorModifier::ProcessDoorArray(SDK::DoorArray* doorArray, DoorAction action, bool enable)
{
    if (!doorArray) return;

    const auto localPlayerPosition = Utils::GetPosVec3(Utils::GetLocalPlayer());

    for (uint32_t i = 0; i < 65535; i++)
    {
        SDK::Door* door = doorArray->Vector[i];
        if (!door) break;

        try
        {
            switch (action)
            {
            case DoorAction::ToggleInteraction:
                SDK::Door_DisableOrEnableDoor(door, enable, false, nullptr);
                break;

            case DoorAction::TeleportToPlayer:
            {
                const auto transform = SDK::Component_Get_Transform(reinterpret_cast<SDK::Component*>(door), nullptr);
                if (transform)
                {
                    const auto currentParent = SDK::Transform_Get_Parent(transform, nullptr);
                    if (currentParent)
                    {
                        const auto worldPosition = SDK::Transform_Get_Position(transform, nullptr);
                        const auto worldRotation = SDK::Transform_Get_Rotation(transform, nullptr);

                        SDK::Transform_Set_Parent(transform, nullptr, nullptr);
                        SDK::Transform_Set_Position(transform, worldPosition, nullptr);
                        SDK::Transform_Set_Rotation(transform, worldRotation, nullptr);
                    }

                    const auto rigidBody = door->Fields.Rigidbody;
                    if (rigidBody)
                    {
                        if (SDK::Rigidbody_Get_Constraints(rigidBody, nullptr) != SDK::RigidbodyConstraints::None)
                            SDK::Rigidbody_Set_Constraints(rigidBody, SDK::RigidbodyConstraints::None, nullptr);

                        SDK::Rigidbody_Set_IsKinematic(rigidBody, true, nullptr);
                    }

                    SDK::Transform_Set_Position(transform, localPlayerPosition, nullptr);
                }
                break;
            }

            case DoorAction::DisableAll:
            {
                SDK::GameObject* doorGO = SDK::Component_Get_GameObject(reinterpret_cast<SDK::Component*>(door), nullptr);
                if (doorGO && SDK::GameObject_get_activeSelf(doorGO, nullptr))
                {
                    SDK::GameObject_SetActive(doorGO, false, nullptr);
                }
                break;
            }

            case DoorAction::EnableAll:
            {
                SDK::GameObject* doorGO = SDK::Component_Get_GameObject(reinterpret_cast<SDK::Component*>(door), nullptr);
                if (doorGO && !SDK::GameObject_get_activeSelf(doorGO, nullptr))
                {
                    SDK::GameObject_SetActive(doorGO, true, nullptr);
                }
                break;
            }
            }
        }
        catch (...)
        {
        }
    }
}
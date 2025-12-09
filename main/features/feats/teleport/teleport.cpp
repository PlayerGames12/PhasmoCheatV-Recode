#include "teleport.h"
using namespace PhasmoCheatV::Features::Movement;

Teleport::Teleport() : FeatureCore("Teleport", TYPE_MOVEMENT)
{
    auto config = GetConfigManager();
    DECLARE_CONFIG(config, "SavedPointX", float, 0.0f);
    DECLARE_CONFIG(config, "SavedPointY", float, 0.0f);
    DECLARE_CONFIG(config, "SavedPointZ", float, 0.0f);
    DECLARE_CONFIG(config, "HasSavedPoint", bool, false);
}

void Teleport::OnMenuRender()
{
    auto config = GetConfigManager();
    if (ImGui::Button("Save current position##teleport"))
        SaveCurrentPosition();
    ImGui::SameLine();
    if (ImGui::Button("Teleport to saved point##teleport"))
        TeleportToSavedPoint();
    static float customX = 0.0f, customY = 0.0f, customZ = 0.0f;
    ImGui::InputFloat("X##teleport", &customX, 0.1f, 1.0f, "%.2f");
    ImGui::InputFloat("Y##teleport", &customY, 0.1f, 1.0f, "%.2f");
    ImGui::InputFloat("Z##teleport", &customZ, 0.1f, 1.0f, "%.2f");
    if (ImGui::Button("Teleport to coordinates##teleport"))
        TeleportToCoordinates(customX, customY, customZ);
    ImGui::Separator();
    ImGui::Text("Items Teleport:");
    if (InGame::mapController)
        TeleportItems();
    ImGui::Separator();
    if (ImGui::Button("Teleport bone##teleport"))
        TeleportBone();
    if (ImGui::Button("Teleport to Truck"))
		TeleportToTruck();
    ImGui::SameLine();
    if (ImGui::Button("Teleport to Ghost"))
        TeleportToGhost();
}

void Teleport::TeleportItems()
{
    const auto localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer)
        return;
    auto objects = SDK::GameObject_FindGameObjectsWithTag(Utils::SysStrToUnityStr("Item"), nullptr);
    if (!objects)
        return;
    uint32_t length = 0;
    memcpy(&length, reinterpret_cast<uint8_t*>(objects) + 0x18, sizeof(uint32_t));
    if (length == 0)
        return;
    const auto localPosition = Utils::GetPosVec3(localPlayer);
    static int selectedItemIndex = 0;
    static std::vector<std::string> itemNames;
    static std::vector<SDK::GameObject*> itemObjects;
    static bool itemsCached = false;
    if (ImGui::Button("Refresh items list##teleport"))
    {
        itemNames.clear();
        itemObjects.clear();
        for (uint32_t i = 0; i < length; ++i)
        {
            SDK::GameObject* object = nullptr;
            memcpy(&object, reinterpret_cast<uint8_t*>(objects) + 0x20 + i * sizeof(void*), sizeof(void*));
            if (!object)
                continue;
            auto namePtr = SDK::Object_Get_Name(reinterpret_cast<SDK::Object*>(object), nullptr);
            if (namePtr)
            {
                std::string itemName = Utils::UnityStrToSysStr(*namePtr);
                itemNames.push_back(itemName + "##" + std::to_string(i));
                itemObjects.push_back(object);
            }
        }
        if (!itemNames.empty())
        {
            selectedItemIndex = 0;
            itemsCached = true;
            NOTIFY_INFO_QUICK("Items list refreshed!");
        }
        else
        {
            NOTIFY_WARNING_QUICK("No items found.");
        }
    }
    if (itemsCached && !itemNames.empty())
    {
        ImGui::Separator();
        ImGui::Text("Select item to teleport:");
        static std::vector<const char*> itemNamesCStr;
        itemNamesCStr.clear();
        for (const auto& name : itemNames)
        {
            itemNamesCStr.push_back(name.c_str());
        }
        ImGui::Combo("##ItemSelect", &selectedItemIndex, itemNamesCStr.data(), itemNamesCStr.size());
        ImGui::SameLine();
        if (ImGui::Button("Teleport selected##teleport"))
        {
            if (selectedItemIndex >= 0 && selectedItemIndex < itemObjects.size())
            {
                auto object = itemObjects[selectedItemIndex];
                auto transform = SDK::GameObject_get_transform(object, nullptr);
                if (transform)
                {
                    auto photonViewType = SDK::System_Type_GetType(Utils::SysStrToUnityStr("Photon.Pun.PhotonView"), nullptr);
                    auto photonView = reinterpret_cast<SDK::PhotonView*>(SDK::GameObject_GetComponent(object, photonViewType, nullptr));
                    if (photonView)
                    {
                        SDK::PhotonView_RequestOwnership(photonView, nullptr);
                    }

                    SDK::Vector3 newPosition = localPosition;
                    newPosition.Y += 0.5f;
                    SDK::Transform_Set_Position(transform, newPosition, nullptr);
                    NOTIFY_INFO_QUICK("Item teleported!");
                }
            }
        }
        ImGui::SameLine();
    }
    else if (!itemsCached)
    {
        ImGui::Text("Click 'Refresh items list' to see available items");
    }
    else
    {
        ImGui::Text("No items found in the game");
    }

    if (ImGui::Button("Teleport all items##teleport"))
    {
        int teleportedCount = 0;
        for (uint32_t i = 0; i < length; ++i)
        {
            SDK::GameObject* object = nullptr;
            memcpy(&object, reinterpret_cast<uint8_t*>(objects) + 0x20 + i * sizeof(void*), sizeof(void*));
            if (!object)
                continue;
            auto transform = SDK::GameObject_get_transform(object, nullptr);
            if (!transform)
                continue;

            auto photonViewType = SDK::System_Type_GetType(Utils::SysStrToUnityStr("Photon.Pun.PhotonView"), nullptr);
            auto photonView = reinterpret_cast<SDK::PhotonView*>(SDK::GameObject_GetComponent(object, photonViewType, nullptr));
            if (photonView)
            {
                SDK::PhotonView_RequestOwnership(photonView, nullptr);
            }

            SDK::Vector3 newPosition = localPosition;
            newPosition.Y += 0.5f;
            SDK::Transform_Set_Position(transform, newPosition, nullptr);
            teleportedCount++;
        }
        char msg[128];
        snprintf(msg, sizeof(msg), "Teleported %d items to your position!", teleportedCount);
        NOTIFY_INFO(msg, 3.0f);
    }
}

void Teleport::TeleportBone()
{
    if (!InGame::mapController || !InGame::evidenceController)
        return NOTIFY_ERROR_QUICK("You need to be in the game.");
    const auto localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer)
        return;
    const auto localPosition = Utils::GetPosVec3(localPlayer);
    const auto evidenceList = InGame::evidenceController->Fields.EvidenceList;
    if (!evidenceList || !evidenceList->Fields.Items || evidenceList->Fields.Size <= 0)
        return;
    const auto& items = evidenceList->Fields.Items->Vector;
    const uint32_t count = evidenceList->Fields.Size;
    for (uint32_t i = 0; i < count; i++)
    {
        const auto evidence = items[i];
        if (!evidence || !evidence->Fields.MediaValues)
            continue;
        const auto evidenceType = evidence->Fields.MediaValues->Fields.EvidenceType;
        if (evidenceType != SDK::EvidenceType::DNA)
            continue;
        auto transform = SDK::Component_Get_Transform(reinterpret_cast<SDK::Component*>(evidence), nullptr);
        if (!transform)
            continue;

        auto gameObject = SDK::Component_Get_GameObject(reinterpret_cast<SDK::Component*>(evidence), nullptr);
        if (gameObject)
        {
            auto photonViewType = SDK::System_Type_GetType(Utils::SysStrToUnityStr("Photon.Pun.PhotonView"), nullptr);
            auto photonView = reinterpret_cast<SDK::PhotonView*>(SDK::GameObject_GetComponent(gameObject, photonViewType, nullptr));
            if (photonView)
            {
                SDK::PhotonView_RequestOwnership(photonView, nullptr);
            }
        }

        SDK::Vector3 newPosition = localPosition;
        newPosition.Y += 0.5f;
        SDK::Transform_Set_Position(transform, newPosition, nullptr);
        NOTIFY_INFO_QUICK("Bone teleported!");
        return;
    }
    NOTIFY_WARNING_QUICK("Bone not found.");
}

void Teleport::SaveCurrentPosition()
{
    const auto localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer)
        return NOTIFY_ERROR_QUICK("Local player not found.");
    SDK::Vector3 savedPoint = Utils::GetPosVec3(localPlayer);
    auto config = GetConfigManager();
    SET_CONFIG_VALUE(config, "SavedPointX", float, savedPoint.X);
    SET_CONFIG_VALUE(config, "SavedPointY", float, savedPoint.Y);
    SET_CONFIG_VALUE(config, "SavedPointZ", float, savedPoint.Z);
    SET_CONFIG_VALUE(config, "HasSavedPoint", bool, true);
    NOTIFY_INFO_QUICK("Saved current position!");
}

void Teleport::TeleportToSavedPoint()
{
    auto config = GetConfigManager();
    if (!CONFIG_BOOL(config, "HasSavedPoint"))
        return NOTIFY_WARNING_QUICK("No saved point found.");
    const auto localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer)
        return NOTIFY_ERROR_QUICK("Local player not found.");
    SDK::Vector3 savedPoint;
    savedPoint.X = CONFIG_FLOAT(config, "SavedPointX");
    savedPoint.Y = CONFIG_FLOAT(config, "SavedPointY");
    savedPoint.Z = CONFIG_FLOAT(config, "SavedPointZ");
    Utils::TpPlayerToVec3(localPlayer, savedPoint);
    NOTIFY_INFO_QUICK("Teleported to saved point!");
}

void Teleport::TeleportToCoordinates(float x, float y, float z)
{
    const auto localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer)
        return NOTIFY_ERROR_QUICK("Local player not found.");
    SDK::Vector3 position{ x, y, z };
    Utils::TpPlayerToVec3(localPlayer, position);
    char msg[128];
    snprintf(msg, sizeof(msg), "Teleported to: X=%.2f Y=%.2f Z=%.2f", x, y, z);
    NOTIFY_INFO(msg, 3.0f);
}

void Teleport::TeleportToTruck()
{
    auto localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer)
        return NOTIFY_ERROR_QUICK("Local player not found.");
    if (!InGame::mapController) // Not necessarily
        return NOTIFY_ERROR_QUICK("You need to be in the game."); 

    SDK::String* tagName = Utils::SysStrToUnityStr("Truck");
    SDK::GameObjectArray* truckObjects = SDK::GameObject_FindGameObjectsWithTag(tagName, nullptr);
    if (!truckObjects)
        return NOTIFY_ERROR_QUICK("Truck not found.");

    for (uint32_t i = 0; i < 65535; i++)
    {
        SDK::GameObject* object = nullptr;
        memcpy(&object, reinterpret_cast<uint8_t*>(truckObjects) + 0x20 + i * sizeof(void*), sizeof(void*));
        if (!object)
            break;

        auto namePtr = SDK::Object_Get_Name(reinterpret_cast<SDK::Object*>(object), nullptr);
        if (!namePtr)
            continue;

        std::string objectName = Utils::UnityStrToSysStr(*namePtr);

        if (objectName == "Truck Floor Collider" && objectName.find("Truck") != std::string::npos)
        {
            auto transform = SDK::GameObject_get_transform(object, nullptr);
            if (transform)
            {
                auto position = SDK::Transform_Get_Position(transform, nullptr);
                Utils::TpPlayerToVec3(localPlayer, position);
                NOTIFY_INFO_QUICK("Teleported to Truck.");
                return;
            }
        }
    }

    NOTIFY_ERROR_QUICK("Truck not found.");
}

void Teleport::TeleportToGhost()
{
    auto localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer)
        return NOTIFY_ERROR_QUICK("Local player not found.");
    if (!InGame::ghostAI)
        return NOTIFY_ERROR_QUICK("Ghost not found.");
	auto ghostVec3 = Utils::GetPosVec3(InGame::ghostAI);
    Utils::TpPlayerToVec3(localPlayer, ghostVec3);
    NOTIFY_INFO_QUICK("Teleported to Ghost.");
}
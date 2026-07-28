#include "playermodifier.h"

using namespace PhasmoCheatV::Features::Players;

PlayerModifier::PlayerModifier() : FeatureCore(LANG("PlayerModifier_Header"), TYPE_PLAYERS) {}

void PlayerModifier::OnMenuRender()
{
    const auto players = Utils::GetAllPlayers();
    if (!players)
    {
        ImGui::Text("%s", LANG("NeedToBeInGame"));
        return;
    }

    const auto localPlayer = Utils::GetLocalPlayer();
    const bool isLocalMasterClient = Utils::IsLocalMasterClient();

    for (int i = 0; i < players->Fields.Size; i++)
    {
        const auto player = players->Fields.Items->Vector[i];
        const bool isLocal = player == localPlayer;

        ImGui::Text("%s: %s",
            LANG("Player"),
            Utils::GetPlayerName(player).c_str()
        );

        ImGui::Text("%s: %s",
            LANG("Sanity"),
            player->Fields.IsDead
            ? LANG("Dead")
            : std::to_string(
                static_cast<int>(Utils::GetPlayerSanity(player))
            ).c_str()
        );

        if (const auto room = player->Fields.LevelRoom;
            room && room->Fields.RoomName)
        {
            ImGui::Text("%s: %s",
                LANG("CurrentRoom"),
                Utils::UnityStrToSysStr(*room->Fields.RoomName).c_str()
            );
        }

        {
            std::string label = std::string(LANG("TeleportTo")) + "###tp_" + std::to_string(i);
            if (ImGui::Button(label.c_str()))
            {
                if (player == localPlayer)
                    NOTIFY_ERROR_QUICK(LANG("CantTeleportToYourself"));
                else
                    Utils::TpPlayerToPlayer(localPlayer, player);
            }
        }

        ImGui::SameLine();

        if (!player->Fields.IsDead && (isLocal || isLocalMasterClient))
        {
            static int sanityValue = 100;

            std::string sliderLabel = std::string(LANG("SanityValue")) + "###sanity_" + std::to_string(i);
            ImGui::SliderInt(sliderLabel.c_str(), &sanityValue, 0, 100);

            std::string btnLabel = std::string(LANG("SetSanity")) + "###setsanity_" + std::to_string(i);

            if (ImGui::Button(btnLabel.c_str()))
            {
                ChangeSanityPlayer(isLocal, player, Utils::toSanityOrInsanity(sanityValue));
            }
        }

        ImGui::SameLine();

        if (player->Fields.IsDead && (isLocal || isLocalMasterClient))
        {
            std::string reviveLabel = std::string(LANG("RevivePlayer")) + "###revive_" + std::to_string(i);
            if (ImGui::Button(reviveLabel.c_str()))
                RevivePlayer(player);
        }

        ImGui::SameLine();

        if (!player->Fields.IsDead && isLocalMasterClient)
        {
            std::string setBansheeTarget = std::string(LANG("SetBansheeTarget")) + "###bansheetrg_" + std::to_string(i);
            if (ImGui::Button(setBansheeTarget.c_str()))
                SetBansheeTarget(player);
        }

        ImGui::Separator();
    }
}

void PlayerModifier::ChangeSanityPlayer(bool isLocal, SDK::Player* player, float sanity)
{
    if (isLocal)
    {
        auto localPlayer = Utils::GetLocalPlayer();
        if (!localPlayer)
        {
            NOTIFY_ERROR_QUICK(LANG("LocalPlayerNotFounded"));
            LOG_ERROR("Localplayer not founded. local");
            return;
        }

        auto playerSanity = localPlayer->Fields.PlayerSanity;
        if (!playerSanity)
        {
            NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
            LOG_ERROR("PlayerSanity not founded. local");
            return;
        }

        SDK::PlayerSanity_SetInsanity(playerSanity, sanity, nullptr);
        NOTIFY_SUCCESS_QUICK(std::vformat(LANG("SanitySuccessfulChanged"), std::make_format_args(sanity)));

        return;
    }
    
    if (player)
    {
        bool isMasterClient = SDK::PhotonNetwork_Get_IsMasterClient(nullptr);
        if (!isMasterClient)
        {
            NOTIFY_ERROR_QUICK(LANG("NeedMustBeHost"));
            return;
        }

        auto playerSanity = player->Fields.PlayerSanity;
        if (!playerSanity)
        {
            NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
            LOG_ERROR("PlayerSanity not founded. other");
            return;
        }

        auto photonView = playerSanity->Fields.photonView;
        if (!photonView)
        {
            NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
            LOG_ERROR("PhotonView not founded");
            return;
        }

        auto floatClass = il2cpp_get_class("mscorlib", "System", "Single");
        if (!floatClass)
            return;

        void* boxedFloat = il2cpp_value_box(floatClass, &sanity);
        if (!boxedFloat)
            return;

        std::vector<void*> params{ boxedFloat };

        auto parameters = Utils::VectorToIl2CppArray<void*>(
            params, "mscorlib", "System", "Object");

        if (!parameters)
            return;

        auto* methodName = Utils::SysStrToUnityStr("NetworkedUpdatePlayerSanity");
        if (!methodName)
            return;

        SDK::PhotonView_RPC(
            photonView,
            methodName,
            SDK::RpcTarget::All,
            parameters,
            nullptr
        );

        NOTIFY_SUCCESS_QUICK(std::vformat(LANG("SanitySuccessfulChanged"), std::make_format_args(sanity)));

        return;
    }

    NOTIFY_ERROR_QUICK(LANG("PlayerNotFounded"));
    LOG_ERROR("Player not founded.");
}

void PlayerModifier::RevivePlayer(SDK::Player* player)
{
    bool isMasterClient = SDK::PhotonNetwork_Get_IsMasterClient(nullptr);
    /*if (!isMasterClient)
    {
        NOTIFY_ERROR_QUICK(LANG("NeedMustBeHost"));
        return;
    }
    */ // removed here

    if (!player)
    {
        NOTIFY_ERROR_QUICK(LANG("PlayerNotFounded"));
        return;
    }

    auto photonView = player->Fields.MonoBehaviourPunFields.pvCache;
    if (!photonView)
    {
        NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
        LOG_ERROR("photonView is null");
        return;
    }

    if (!isMasterClient && !SDK::PhotonView_get_IsMine(photonView, nullptr)) // by Checks$$IsRealSenderOrHost // dont remove this check
    {
        NOTIFY_ERROR_QUICK(LANG("NeedMustBeHostOrLocal"));
        return;
    }

    if (!player->Fields.IsDead) // dont remove this check
    {
        NOTIFY_ERROR_QUICK(LANG("PlayerAlreadyAlive"));
        return;
    }

    auto levelValues = Utils::GetLevelValues();
    if (!levelValues)
    {
        NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
        return;
    }

    auto currentDifficulty = levelValues->Fields.currentDifficulty;
    if (!currentDifficulty)
    {
        NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
        return;
    }

    auto cursedItemsArray = currentDifficulty->Fields.actualCursedItems;
    if (!cursedItemsArray)
    {
        NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
        LOG_ERROR("cursedItemsArray is null");
        return;
    }

    bool cursedItemsOK = false;

    for (int32_t i = 0; i < cursedItemsArray->MaxLength; i++)
    {
        auto cursedItemType = cursedItemsArray->Vector[i];
        if (cursedItemType == SDK::DiffCursedItems::none)
            continue;

        if (cursedItemType == SDK::DiffCursedItems::monkeyPaw || cursedItemType == SDK::DiffCursedItems::tarotCards) // dont remove this check
        {
            cursedItemsOK = true;
            break;
        }
    }

    if (!cursedItemsOK) // dont remove this check
    {
        NOTIFY_ERROR_QUICK(LANG("NeedPawOrCards"));
        return;
    }

    auto* methodName = Utils::SysStrToUnityStr("Revive");
    if (!methodName)
        return;

    SDK::PhotonView_RPC(
        photonView,
        methodName,
        SDK::RpcTarget::All,
        nullptr,
        nullptr
    );

    NOTIFY_SUCCESS_QUICK(LANG("PlayerSuccessRevived"));
}

void PlayerModifier::SetBansheeTarget(SDK::Player* player)
{
    if (!player)
    {
        NOTIFY_ERROR_QUICK(LANG("PlayerNotFounded"));
        return;
    }

    bool isMasterClient = SDK::PhotonNetwork_Get_IsMasterClient(nullptr);
    if (!isMasterClient)
    {
        NOTIFY_ERROR_QUICK(LANG("NeedMustBeHost"));
        return;
    }

    if (!Utils::GetGhostAI())
    {
        NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
        LOG_ERROR("Ghost is null");
        return;
    }

    auto ghostInfo = Utils::GetGhostAI()->Fields.GhostInfo;

    if (!ghostInfo)
    {
        NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
        LOG_ERROR("GhostInfo is null");
        return;
    }

    auto currentGhost = ghostInfo->Fields.GhostTraits.GhostType_;

    if (currentGhost != SDK::GhostType::Banshee)
    {
        NOTIFY_ERROR_QUICK(LANG("GhostIsntBanshee"));
        return;
    }

    auto photonView = player->Fields.MonoBehaviourPunFields.pvCache;
    if (!photonView)
    {
        NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
        LOG_ERROR("player photonView is null");
        return;
    }

    auto prPlayer = SDK::PhotonView_get_Owner(photonView, nullptr);
    if (!prPlayer)
    {
        NOTIFY_ERROR_QUICK(LANG("PlayerNotFounded"));
        return;
    }

    int32_t targetId = -1;
    targetId = SDK::PRPlayer_get_ActorNumber(prPlayer, nullptr);

    if (targetId < 0)
    {
        NOTIFY_ERROR_QUICK(LANG("PlayerNotFounded"));
        return;
    }

    auto photonViewGhost = Utils::GetGhostAI()->Fields.MonoBehaviourPunFields.pvCache;
    if (!photonViewGhost)
    {
        NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
        LOG_ERROR("Ghost photonView is null");
        return;
    }

    auto intClass = il2cpp_get_class("mscorlib", "System", "Int32");
    if (!intClass)
        return;

    void* boxedInt = il2cpp_value_box(intClass, &targetId);
    if (!boxedInt)
        return;

    std::vector<void*> params{ boxedInt };

    auto parameters = Utils::VectorToIl2CppArray<void*>(
        params,
        "mscorlib",
        "System",
        "Object");

    if (!parameters)
        return;

    auto* methodName = Utils::SysStrToUnityStr("SetBansheeTargetNetworked");
    if (!methodName)
        return;

    SDK::PhotonView_RPC(
        photonViewGhost,
        methodName,
        SDK::RpcTarget::All,
        parameters,
        nullptr
    );

    NOTIFY_SUCCESS_QUICK(std::format("BansheeTargetSetSuccessful", Utils::GetPlayerName(player)));
}
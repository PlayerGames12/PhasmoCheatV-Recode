#include "playermodifier.h"

using namespace PhasmoCheatV::Features::Players;

PlayerModifier::PlayerModifier() : FeatureCore("Player Modifier", TYPE_PLAYERS) {}

void PlayerModifier::OnMenuRender()
{
    const auto players = Utils::GetAllPlayers();
    if (!players)
        return ImGui::Text("You need to be in the game.");

    for (int playerIndex = 0; playerIndex < players->Fields.Size; playerIndex++)
    {
        const auto localPlayer = Utils::GetLocalPlayer();
        const auto player = players->Fields.Items->Vector[playerIndex];

        ImGui::Text("Player: %s", Utils::GetPlayerName(player).c_str());
        ImGui::Text("Sanity: %s", player->Fields.IsDead ? "DEAD" : std::to_string(static_cast<int>(100.f - Utils::GetPlayerSanity(player))).c_str());

        if (const auto levelRoom = player->Fields.LevelRoom; levelRoom && levelRoom->Fields.RoomName)
            ImGui::Text("Current room: %s", Utils::UnityStrToSysStr(*player->Fields.LevelRoom->Fields.RoomName).c_str());

        const auto teleportToLabel = std::format("Teleport to##{}", playerIndex);
        if (ImGui::Button(teleportToLabel.c_str()))
        {
            if (localPlayer == player)
            {
                NOTIFY_ERROR_QUICK("You can't teleport to yourself.");
            }
            else
            {
                Utils::TpPlayerToPlayer(localPlayer, player);
            }
        }

        ImGui::SameLine();

        if (const auto isLocalMasterClient = Utils::IsLocalMasterClient(); player == Utils::GetLocalPlayer() || isLocalMasterClient)
        {
            const auto killPlayerLabel = std::format("Kill player##{}", playerIndex);
            if (ImGui::Button(killPlayerLabel.c_str()))
            {
                if (player->Fields.IsDead)
                {
                    NOTIFY_ERROR_QUICK("Player is already dead.");
                }
                else
                {
                    isLocalMasterClient ? SDK::Player_StartKillingPlayer(player, nullptr) : SDK::Player_KillPlayer(player, nullptr);
                }
            }

            ImGui::SameLine();

            const auto RevivePlayerLaval = std::format("Revive Player##{}", playerIndex);
            if (ImGui::Button(RevivePlayerLaval.c_str()))
            {
                if (!player->Fields.IsDead)
                {
                    NOTIFY_ERROR_QUICK("Player is already revived.");
                }
                else
                {
                    if (isLocalMasterClient)
                        SDK::Player_RevivePlayer(player, true, nullptr);
                    else
                        SDK::Player_Revive(player, nullptr, nullptr);
                }
            }

            const auto freezePlayerLabel = std::format("Freeze player##{}", playerIndex);
            if (ImGui::Button(freezePlayerLabel.c_str()))
                SDK::Player_ToggleFreezePlayer(player, true, nullptr);

            ImGui::SameLine();

            const auto unfreezePlayerLabel = std::format("Unfreeze player##{}", playerIndex);
            if (ImGui::Button(unfreezePlayerLabel.c_str()))
                SDK::Player_ToggleFreezePlayer(player, false, nullptr);

            if (!player->Fields.IsDead)
            {
                static int currentSanityValue = 100;
                const auto sanityLabel = std::format("Sanity##i{}", playerIndex);
                ImGui::SliderInt(sanityLabel.c_str(), &currentSanityValue, 0, 100);
                ImGui::SameLine();
                const auto setSanityLabel = std::format("Set sanity##i{}", playerIndex);
                if (ImGui::Button(setSanityLabel.c_str()))
                {
                    SDK::PlayerSanity_SetInsanity(player->Fields.PlayerSanity, 100 - currentSanityValue, nullptr);
                }
            }
        }

        ImGui::Separator();
    }
}
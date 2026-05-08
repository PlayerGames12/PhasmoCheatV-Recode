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

        ImGui::Text("%s: %s",
            LANG("Player"),
            Utils::GetPlayerName(player).c_str()
        );

        ImGui::Text("%s: %s",
            LANG("Sanity"),
            player->Fields.IsDead
            ? LANG("Dead")
            : std::to_string(
                static_cast<int>(100.f - Utils::GetPlayerSanity(player))
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

        if (player == localPlayer || isLocalMasterClient)
        {
            if (!player->Fields.IsDead)
            {
                static int sanityValue = 100;

                std::string sliderLabel = std::string(LANG("SanityValue")) + "###sanity_" + std::to_string(i);
                ImGui::SliderInt(sliderLabel.c_str(), &sanityValue, 0, 100);

                std::string btnLabel = std::string(LANG("SetSanity")) + "###setsanity_" + std::to_string(i);
                if (ImGui::Button(btnLabel.c_str()))
                {
                    SDK::PlayerSanity_SetInsanity(
                        player->Fields.PlayerSanity,
                        100 - sanityValue,
                        nullptr
                    );
                }
            }
        }

        ImGui::Separator();
    }
}


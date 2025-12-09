#include "playeresp.h"

using namespace PhasmoCheatV::Features::Visuals;

const std::vector<SDK::HumanBodyBones> PlayerESP::MAIN_BONES = {
    SDK::HumanBodyBones::Hips,
    SDK::HumanBodyBones::Spine,
    SDK::HumanBodyBones::Chest,
    SDK::HumanBodyBones::Neck,
    SDK::HumanBodyBones::Head,
    SDK::HumanBodyBones::LeftShoulder,
    SDK::HumanBodyBones::LeftUpperArm,
    SDK::HumanBodyBones::LeftLowerArm,
    SDK::HumanBodyBones::LeftHand,
    SDK::HumanBodyBones::RightShoulder,
    SDK::HumanBodyBones::RightUpperArm,
    SDK::HumanBodyBones::RightLowerArm,
    SDK::HumanBodyBones::RightHand,
    SDK::HumanBodyBones::LeftUpperLeg,
    SDK::HumanBodyBones::LeftLowerLeg,
    SDK::HumanBodyBones::LeftFoot,
    SDK::HumanBodyBones::LeftToes,
    SDK::HumanBodyBones::RightUpperLeg,
    SDK::HumanBodyBones::RightLowerLeg,
    SDK::HumanBodyBones::RightFoot,
    SDK::HumanBodyBones::RightToes
};

const std::vector<std::pair<SDK::HumanBodyBones, SDK::HumanBodyBones>> PlayerESP::SKELETON_CONNECTIONS = {

    {SDK::HumanBodyBones::Hips, SDK::HumanBodyBones::Spine},
    {SDK::HumanBodyBones::Spine, SDK::HumanBodyBones::Chest},
    {SDK::HumanBodyBones::Chest, SDK::HumanBodyBones::Neck},
    {SDK::HumanBodyBones::Neck, SDK::HumanBodyBones::Head},

    {SDK::HumanBodyBones::Chest, SDK::HumanBodyBones::LeftShoulder},
    {SDK::HumanBodyBones::LeftShoulder, SDK::HumanBodyBones::LeftUpperArm},
    {SDK::HumanBodyBones::LeftUpperArm, SDK::HumanBodyBones::LeftLowerArm},
    {SDK::HumanBodyBones::LeftLowerArm, SDK::HumanBodyBones::LeftHand},

    {SDK::HumanBodyBones::Chest, SDK::HumanBodyBones::RightShoulder},
    {SDK::HumanBodyBones::RightShoulder, SDK::HumanBodyBones::RightUpperArm},
    {SDK::HumanBodyBones::RightUpperArm, SDK::HumanBodyBones::RightLowerArm},
    {SDK::HumanBodyBones::RightLowerArm, SDK::HumanBodyBones::RightHand},

    {SDK::HumanBodyBones::Hips, SDK::HumanBodyBones::LeftUpperLeg},
    {SDK::HumanBodyBones::LeftUpperLeg, SDK::HumanBodyBones::LeftLowerLeg},
    {SDK::HumanBodyBones::LeftLowerLeg, SDK::HumanBodyBones::LeftFoot},
    {SDK::HumanBodyBones::LeftFoot, SDK::HumanBodyBones::LeftToes},

    {SDK::HumanBodyBones::Hips, SDK::HumanBodyBones::RightUpperLeg},
    {SDK::HumanBodyBones::RightUpperLeg, SDK::HumanBodyBones::RightLowerLeg},
    {SDK::HumanBodyBones::RightLowerLeg, SDK::HumanBodyBones::RightFoot},
    {SDK::HumanBodyBones::RightFoot, SDK::HumanBodyBones::RightToes}
};

PlayerESP::PlayerESP() : FeatureCore("Player ESP", TYPE_VISUALS)
{
    DECLARE_CONFIG(GetConfigManager(), "ShowPlayerSanity", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowDeadStatus", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowBox", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowRoom", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowPrestige", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowExperience", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowLevel", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowSprinting", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "ShowSkeleton", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "Color", ImColor, ImColor(255, 255, 255, 255));
}

void PlayerESP::OnRender()
{
    if (!IsActive() || InGame::ghostAI == nullptr)
        return;

    const auto players = Utils::GetAllPlayers();
    const auto localPlayer = Utils::GetLocalPlayer();

    if (players == nullptr || localPlayer == nullptr)
        return;

    const bool showSanity = CONFIG_BOOL(GetConfigManager(), "ShowPlayerSanity");
    const bool showDeadStatus = CONFIG_BOOL(GetConfigManager(), "ShowDeadStatus");
    const bool showBox = CONFIG_BOOL(GetConfigManager(), "ShowBox");
    const bool showRoom = CONFIG_BOOL(GetConfigManager(), "ShowRoom");
    const bool showPrestige = CONFIG_BOOL(GetConfigManager(), "ShowPrestige");
    const bool showExperience = CONFIG_BOOL(GetConfigManager(), "ShowExperience");
    const bool showLevel = CONFIG_BOOL(GetConfigManager(), "ShowLevel");
    const bool showSprinting = CONFIG_BOOL(GetConfigManager(), "ShowSprinting");
    const bool showSkeleton = CONFIG_BOOL(GetConfigManager(), "ShowSkeleton");
    const ImColor color = CONFIG_COLOR(GetConfigManager(), "Color");

    const auto draw = ImGui::GetBackgroundDrawList();
    const int playerCount = players->Fields.Size;
    const auto& playerVector = players->Fields.Items->Vector;

    for (int playerIndex = 0; playerIndex < playerCount; playerIndex++)
    {
        const auto player = playerVector[playerIndex];
        if (player == nullptr || player == localPlayer)
            continue;

        std::unordered_map<SDK::HumanBodyBones, SDK::Vector3> bonePositions;
        if (!GetBonePositions(player, bonePositions))
            continue;

        ImVec2 boxMin, boxMax;
        bool hasValidBox = CalculateBoundingBox(bonePositions, boxMin, boxMax);

        if (showSkeleton)
        {
            DrawSkeleton(player, color, 1.5f);
        }

        if (showBox && hasValidBox)
        {
            draw->AddRect(boxMin, boxMax, color);
        }

        SDK::Vector3 headScreenPos;
        bool hasHeadPos = false;
        if (bonePositions.find(SDK::HumanBodyBones::Head) != bonePositions.end())
        {
            SDK::Vector3 headWorldPos = bonePositions[SDK::HumanBodyBones::Head];
            hasHeadPos = Utils::WTS(headWorldPos, headScreenPos) && headScreenPos.Z > 0;
        }

        float infoX, infoY;
        if (hasValidBox)
        {

            infoX = boxMax.x + 5;
            infoY = boxMin.y;
        }
        else if (hasHeadPos)
        {

            infoX = headScreenPos.X + 5;
            infoY = headScreenPos.Y;
        }
        else
        {
            continue;
        }

        std::string playerName = Utils::GetPlayerName(player);

        float nameY, nameX;
        if (hasValidBox)
        {
            nameX = boxMin.x;
            nameY = boxMin.y - 20;
        }
        else if (hasHeadPos)
        {
            nameX = headScreenPos.X;
            nameY = headScreenPos.Y - 20;
        }
        else
        {
            nameX = infoX;
            nameY = infoY - 20;
        }

        draw->AddText(ImVec2(nameX, nameY), color, playerName.c_str());

        float currentInfoY = infoY;

        if (showDeadStatus && player->Fields.IsDead)
        {
            draw->AddText(ImVec2(infoX, currentInfoY), IM_COL32(255, 0, 0, 255), "DEAD");
            currentInfoY += 15;
        }

        if (showRoom)
        {
            if (const auto levelRoom = player->Fields.LevelRoom; levelRoom && levelRoom->Fields.RoomName)
            {
                std::string roomText = "Room: " + Utils::UnityStrToSysStr(*levelRoom->Fields.RoomName);
                draw->AddText(ImVec2(infoX, currentInfoY), color, roomText.c_str());
                currentInfoY += 15;
            }
        }

        if (showPrestige)
        {
            if (const auto network = Utils::GetNetwork(); network && network->Fields.NetworkPlayerSpots)
            {
                const auto spots = network->Fields.NetworkPlayerSpots;
                if (spots && playerIndex < spots->Fields.Size)
                {
                    const auto spot = spots->Fields.Items->Vector[playerIndex];
                    if (spot)
                    {
                        std::string prestigeText = "Prestige: " + std::to_string(spot->Fields.Prestige);
                        draw->AddText(ImVec2(infoX, currentInfoY), color, prestigeText.c_str());
                        currentInfoY += 15;
                    }
                }
            }
        }

        if (showExperience)
        {
            if (const auto network = Utils::GetNetwork(); network && network->Fields.NetworkPlayerSpots)
            {
                const auto spots = network->Fields.NetworkPlayerSpots;
                if (spots && playerIndex < spots->Fields.Size)
                {
                    const auto spot = spots->Fields.Items->Vector[playerIndex];
                    if (spot)
                    {
                        std::string expText = "Exp: " + std::to_string(spot->Fields.Experience);
                        draw->AddText(ImVec2(infoX, currentInfoY), color, expText.c_str());
                        currentInfoY += 15;
                    }
                }
            }
        }

        if (showLevel)
        {
            if (const auto network = Utils::GetNetwork(); network && network->Fields.NetworkPlayerSpots)
            {
                const auto spots = network->Fields.NetworkPlayerSpots;
                if (spots && playerIndex < spots->Fields.Size)
                {
                    const auto spot = spots->Fields.Items->Vector[playerIndex];
                    if (spot)
                    {
                        std::string levelText = "Level: " + std::to_string(spot->Fields.Level);
                        draw->AddText(ImVec2(infoX, currentInfoY), color, levelText.c_str());
                        currentInfoY += 15;
                    }
                }
            }
        }

        if (showSprinting && player->Fields.PlayerStamina)
        {
            if (player->Fields.PlayerStamina->Fields.isSprinting)
            {
                draw->AddText(ImVec2(infoX, currentInfoY), IM_COL32(0, 255, 0, 255), "SPRINTING");
                currentInfoY += 15;
            }
        }

        if (showSanity && !player->Fields.IsDead)
        {
            const float sanity = 100.f - Utils::GetPlayerSanity(player);
            const float barWidth = 8.0f;
            const float barHeight = 50.0f;

            ImVec2 barPos;
            if (hasValidBox)
            {

                barPos = ImVec2(boxMin.x - barWidth - 5, boxMin.y);
            }
            else if (hasHeadPos)
            {

                barPos = ImVec2(headScreenPos.X - barWidth - 5, headScreenPos.Y - barHeight / 2);
            }
            else
            {
                continue;
            }

            draw->AddRectFilled(barPos, ImVec2(barPos.x + barWidth, barPos.y + barHeight), IM_COL32(0, 0, 0, 255));

            float filledHeight = (barHeight * sanity / 100.0f);
            ImVec2 fillEnd = ImVec2(barPos.x + barWidth, barPos.y + filledHeight);
            draw->AddRectFilled(barPos, fillEnd, IM_COL32(255, 255, 0, 255));

            draw->AddRect(barPos, ImVec2(barPos.x + barWidth, barPos.y + barHeight), color);

            std::string sanityText = std::to_string(static_cast<int>(sanity)) + "%";
            const auto textSize = ImGui::CalcTextSize(sanityText.c_str());

            draw->AddText(ImVec2(barPos.x - textSize.x - 2, barPos.y + (barHeight - textSize.y) / 2),
                color, sanityText.c_str());
        }
    }
}

bool PlayerESP::GetBonePositions(const SDK::Player* player, std::unordered_map<SDK::HumanBodyBones, SDK::Vector3>& bonePositions)
{
    if (!player)
        return false;

    auto animator = player->Fields.Animator;
    if (!animator)
        return false;

    for (auto bone : MAIN_BONES)
    {
        SDK::Transform* boneTransform = nullptr;

        try
        {
            boneTransform = SDK::Animator_GetBoneTransform(animator, bone, nullptr);
        }
        catch (const std::exception& e)
        {
            continue;
        }
        catch (...)
        {
            continue;
        }

        if (boneTransform)
        {
            SDK::Vector3 worldPos = Utils::GetPosVec3(boneTransform);
            bonePositions[bone] = worldPos;
        }
    }

    return !bonePositions.empty();
}

bool PlayerESP::CalculateBoundingBox(const std::unordered_map<SDK::HumanBodyBones, SDK::Vector3>& bonePositions, ImVec2& boxMin, ImVec2& boxMax)
{
    float minX = FLT_MAX, maxX = FLT_MIN;
    float minY = FLT_MAX, maxY = FLT_MIN;
    bool hasValidPoints = false;

    for (const auto& bonePair : bonePositions)
    {
        SDK::Vector3 screenPos;
        if (Utils::WTS(bonePair.second, screenPos) && screenPos.Z > 0)
        {
            minX = std::min<float>(minX, screenPos.X);
            maxX = std::max<float>(maxX, screenPos.X);
            minY = std::min<float>(minY, screenPos.Y);
            maxY = std::max<float>(maxY, screenPos.Y);
            hasValidPoints = true;
        }
    }

    if (!hasValidPoints)
        return false;

    const float padding = 5.0f;
    boxMin = ImVec2(minX - padding, minY - padding);
    boxMax = ImVec2(maxX + padding, maxY + padding);

    return true;
}

void PlayerESP::DrawSkeleton(const SDK::Player* player, const ImColor& color, float thickness)
{
    if (!player)
        return;

    std::unordered_map<SDK::HumanBodyBones, SDK::Vector3> bonePositions;
    if (!GetBonePositions(player, bonePositions))
        return;

    auto drawList = ImGui::GetBackgroundDrawList();

    for (const auto& connection : SKELETON_CONNECTIONS)
    {
        auto fromBone = connection.first;
        auto toBone = connection.second;

        if (bonePositions.find(fromBone) == bonePositions.end() ||
            bonePositions.find(toBone) == bonePositions.end())
            continue;

        const auto& fromPos = bonePositions.at(fromBone);
        const auto& toPos = bonePositions.at(toBone);

        SDK::Vector3 fromScreen, toScreen;
        if (Utils::WTS(fromPos, fromScreen) && Utils::WTS(toPos, toScreen) &&
            fromScreen.Z > 0 && toScreen.Z > 0)
        {
            drawList->AddLine(
                ImVec2(fromScreen.X, fromScreen.Y),
                ImVec2(toScreen.X, toScreen.Y),
                color,
                thickness
            );
        }
    }

    for (const auto& bonePair : bonePositions)
    {
        SDK::Vector3 screenPos;
        if (Utils::WTS(bonePair.second, screenPos) && screenPos.Z > 0)
        {
            drawList->AddCircleFilled(
                ImVec2(screenPos.X, screenPos.Y),
                thickness * 0.8f,
                color
            );
        }
    }
}

void PlayerESP::OnMenuRender()
{
    try {
        constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

        bool enabled = IsActive();
        if (ImGui::Checkbox("Enabled##playerESP", &enabled))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
            if (enabled) OnActivate();
            else OnDeactivate();
        }

        if (enabled) {
            ImGui::SameLine();
            ImColor currentColor = CONFIG_COLOR(GetConfigManager(), "Color");
            if (ImGui::ColorEdit4(
                "Color##playerESP",
                reinterpret_cast<float*>(&currentColor.Value),
                colorEditFlags
            ))
            {
                SET_CONFIG_VALUE(GetConfigManager(), "Color", ImColor, currentColor);
            }

            bool showBox = CONFIG_BOOL(GetConfigManager(), "ShowBox");
            if (ImGui::Checkbox("Show 2D box", &showBox))
                SET_CONFIG_VALUE(GetConfigManager(), "ShowBox", bool, showBox);

            bool showSkeleton = CONFIG_BOOL(GetConfigManager(), "ShowSkeleton");
            if (ImGui::Checkbox("Show skeleton", &showSkeleton))
                SET_CONFIG_VALUE(GetConfigManager(), "ShowSkeleton", bool, showSkeleton);

            bool showSanity = CONFIG_BOOL(GetConfigManager(), "ShowPlayerSanity");
            if (ImGui::Checkbox("Show player sanity", &showSanity))
                SET_CONFIG_VALUE(GetConfigManager(), "ShowPlayerSanity", bool, showSanity);

            bool showDeadStatus = CONFIG_BOOL(GetConfigManager(), "ShowDeadStatus");
            if (ImGui::Checkbox("Show dead status", &showDeadStatus))
                SET_CONFIG_VALUE(GetConfigManager(), "ShowDeadStatus", bool, showDeadStatus);

            bool showRoom = CONFIG_BOOL(GetConfigManager(), "ShowRoom");
            if (ImGui::Checkbox("Show current room", &showRoom))
                SET_CONFIG_VALUE(GetConfigManager(), "ShowRoom", bool, showRoom);

            bool showPrestige = CONFIG_BOOL(GetConfigManager(), "ShowPrestige");
            if (ImGui::Checkbox("Show prestige", &showPrestige))
                SET_CONFIG_VALUE(GetConfigManager(), "ShowPrestige", bool, showPrestige);

            bool showExperience = CONFIG_BOOL(GetConfigManager(), "ShowExperience");
            if (ImGui::Checkbox("Show experience", &showExperience))
                SET_CONFIG_VALUE(GetConfigManager(), "ShowExperience", bool, showExperience);

            bool showLevel = CONFIG_BOOL(GetConfigManager(), "ShowLevel");
            if (ImGui::Checkbox("Show level", &showLevel))
                SET_CONFIG_VALUE(GetConfigManager(), "ShowLevel", bool, showLevel);

            bool showSprinting = CONFIG_BOOL(GetConfigManager(), "ShowSprinting");
            if (ImGui::Checkbox("Show sprinting", &showSprinting))
                SET_CONFIG_VALUE(GetConfigManager(), "ShowSprinting", bool, showSprinting);
        }
    }
    catch (const std::exception& e) {
        LOG_ERROR("Error in PlayerESP::OnMenu: " + std::string(e.what()));
        ImGui::Text("Error loading PlayerESP settings");
    }
}
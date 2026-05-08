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

const std::vector<SDK::HumanBodyBones> PlayerESP::ESSENTIAL_BONES = {
    SDK::HumanBodyBones::Head,
    SDK::HumanBodyBones::Neck,
    SDK::HumanBodyBones::Hips,
    SDK::HumanBodyBones::LeftHand,
    SDK::HumanBodyBones::RightHand,
    SDK::HumanBodyBones::LeftFoot,
    SDK::HumanBodyBones::RightFoot
};

PlayerESP::PlayerESP() : FeatureCore(LANG("PlayerESP_Header"), TYPE_VISUALS)
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

    if (players == nullptr || localPlayer == nullptr || players->Fields.Items == nullptr)
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
    const auto& playerVector = players->Fields.Items->Vector;

    const auto network = Utils::GetNetwork();
    const auto spotsList = (network && network->Fields.NetworkPlayerSpots && network->Fields.NetworkPlayerSpots->Fields.Items)
        ? network->Fields.NetworkPlayerSpots
        : nullptr;

    const int playerCount = players->Fields.Size;
    for (int playerIndex = 0; playerIndex < playerCount; playerIndex++)
    {
        const auto player = playerVector[playerIndex];
        if (player == nullptr || player == localPlayer)
            continue;

        std::unordered_map<SDK::HumanBodyBones, SDK::Vector3> bonePositions;
        bonePositions.reserve(showSkeleton ? MAIN_BONES.size() : ESSENTIAL_BONES.size());

        if (!GetBonePositions(player, bonePositions, showSkeleton))
            continue;

        std::unordered_map<SDK::HumanBodyBones, SDK::Vector3> screenBonePositions;
        screenBonePositions.reserve(bonePositions.size());
        for (const auto& [bone, worldPos] : bonePositions)
        {
            SDK::Vector3 screenPos;
            if (Utils::WTS(worldPos, screenPos) && screenPos.Z > 0)
                screenBonePositions.emplace(bone, screenPos);
        }

        if (screenBonePositions.empty())
            continue;

        ImVec2 boxMin, boxMax;
        bool hasValidBox = CalculateBoundingBox(screenBonePositions, boxMin, boxMax);

        if (showSkeleton)
            DrawSkeleton(screenBonePositions, color, 1.5f);

        if (showBox && hasValidBox)
            draw->AddRect(boxMin, boxMax, color);

        SDK::Vector3 headScreenPos{};
        bool hasHeadPos = false;
        if (const auto headIt = screenBonePositions.find(SDK::HumanBodyBones::Head); headIt != screenBonePositions.end())
        {
            headScreenPos = headIt->second;
            hasHeadPos = true;
        }

        float infoX = 0.0f;
        float infoY = 0.0f;
        if (hasValidBox)
        {
            infoX = boxMax.x + 5.0f;
            infoY = boxMin.y;
        }
        else if (hasHeadPos)
        {
            infoX = headScreenPos.X + 5.0f;
            infoY = headScreenPos.Y;
        }
        else
        {
            continue;
        }

        SDK::NetworkPlayerSpot* spot = nullptr;
        if (spotsList && playerIndex < spotsList->Fields.Size)
            spot = spotsList->Fields.Items->Vector[playerIndex];

        std::string playerName;
        if (spot && spot->Fields.AccountName)
            playerName = Utils::UnityStrToSysStr(*spot->Fields.AccountName);
        else
            playerName = Utils::GetPlayerName(player);

        float nameX = 0.0f;
        float nameY = 0.0f;
        if (hasValidBox)
        {
            nameX = boxMin.x;
            nameY = boxMin.y - 20.0f;
        }
        else
        {
            nameX = headScreenPos.X;
            nameY = headScreenPos.Y - 20.0f;
        }

        draw->AddText(ImVec2(nameX, nameY), color, playerName.c_str());

        float currentInfoY = infoY;

        if (showDeadStatus && player->Fields.IsDead)
        {
            draw->AddText(ImVec2(infoX, currentInfoY), IM_COL32(255, 0, 0, 255), "DEAD");
            currentInfoY += 15.0f;
        }

        if (showRoom)
        {
            if (const auto levelRoom = player->Fields.LevelRoom; levelRoom && levelRoom->Fields.RoomName)
            {
                std::string roomText = "Room: " + Utils::UnityStrToSysStr(*levelRoom->Fields.RoomName);
                draw->AddText(ImVec2(infoX, currentInfoY), color, roomText.c_str());
                currentInfoY += 15.0f;
            }
        }

        if (showPrestige && spot)
        {
            std::string prestigeText = "Prestige: " + std::to_string(spot->Fields.Prestige);
            draw->AddText(ImVec2(infoX, currentInfoY), color, prestigeText.c_str());
            currentInfoY += 15.0f;
        }

        if (showExperience && spot)
        {
            std::string expText = "Exp: " + std::to_string(spot->Fields.Experience);
            draw->AddText(ImVec2(infoX, currentInfoY), color, expText.c_str());
            currentInfoY += 15.0f;
        }

        if (showLevel && spot)
        {
            std::string levelText = "Level: " + std::to_string(spot->Fields.Level);
            draw->AddText(ImVec2(infoX, currentInfoY), color, levelText.c_str());
            currentInfoY += 15.0f;
        }

        if (showSanity && !player->Fields.IsDead)
        {
            float sanity = 100.0f - Utils::GetPlayerSanity(player);
            sanity = std::clamp(sanity, 0.0f, 100.0f);

            constexpr float barWidth = 8.0f;
            constexpr float barHeight = 50.0f;

            ImVec2 barPos;
            if (hasValidBox)
                barPos = ImVec2(boxMin.x - barWidth - 5.0f, boxMin.y);
            else
                barPos = ImVec2(headScreenPos.X - barWidth - 5.0f, headScreenPos.Y - (barHeight * 0.5f));

            draw->AddRectFilled(barPos, ImVec2(barPos.x + barWidth, barPos.y + barHeight), IM_COL32(0, 0, 0, 255));

            const float filledHeight = barHeight * (sanity / 100.0f);
            const ImVec2 fillEnd(barPos.x + barWidth, barPos.y + filledHeight);
            draw->AddRectFilled(barPos, fillEnd, IM_COL32(255, 255, 0, 255));
            draw->AddRect(barPos, ImVec2(barPos.x + barWidth, barPos.y + barHeight), color);

            const std::string sanityText = std::to_string(static_cast<int>(sanity)) + "%";
            const ImVec2 textSize = ImGui::CalcTextSize(sanityText.c_str());
            draw->AddText(ImVec2(barPos.x - textSize.x - 2.0f, barPos.y + (barHeight - textSize.y) * 0.5f), color, sanityText.c_str());
        }
    }
}

bool PlayerESP::GetBonePositions(const SDK::Player* player, std::unordered_map<SDK::HumanBodyBones, SDK::Vector3>& bonePositions, bool includeAllBones)
{
    if (!player)
        return false;

    auto animator = player->Fields.Animator;
    if (!animator)
        return false;

    const auto& bonesToRead = includeAllBones ? MAIN_BONES : ESSENTIAL_BONES;
    for (auto bone : bonesToRead)
    {
        SDK::Transform* boneTransform = nullptr;

        try
        {
            boneTransform = SDK::Animator_GetBoneTransform(animator, bone, nullptr);
        }
        catch (const std::exception&)
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
        const SDK::Vector3& screenPos = bonePair.second;
        minX = std::min<float>(minX, screenPos.X);
        maxX = std::max<float>(maxX, screenPos.X);
        minY = std::min<float>(minY, screenPos.Y);
        maxY = std::max<float>(maxY, screenPos.Y);
        hasValidPoints = true;
    }

    if (!hasValidPoints)
        return false;

    const float padding = 5.0f;
    boxMin = ImVec2(minX - padding, minY - padding);
    boxMax = ImVec2(maxX + padding, maxY + padding);

    return true;
}

void PlayerESP::DrawSkeleton(const std::unordered_map<SDK::HumanBodyBones, SDK::Vector3>& bonePositions, const ImColor& color, float thickness)
{
    if (bonePositions.empty())
        return;

    auto drawList = ImGui::GetBackgroundDrawList();

    for (const auto& connection : SKELETON_CONNECTIONS)
    {
        const auto fromIt = bonePositions.find(connection.first);
        const auto toIt = bonePositions.find(connection.second);
        if (fromIt == bonePositions.end() || toIt == bonePositions.end())
            continue;

        drawList->AddLine(
            ImVec2(fromIt->second.X, fromIt->second.Y),
            ImVec2(toIt->second.X, toIt->second.Y),
            color,
            thickness
        );
    }

    for (const auto& bonePair : bonePositions)
    {
        drawList->AddCircleFilled(
            ImVec2(bonePair.second.X, bonePair.second.Y),
            thickness * 0.8f,
            color
        );
    }
}

void PlayerESP::OnMenuRender()
{
    try {
        constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

        bool enabled = IsActive();
        std::string enabledLabel = std::string(LANG("EnablePlayerESP")) + "###playerESP";
        if (ImGui::Checkbox(enabledLabel.c_str(), &enabled))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
            if (enabled) OnActivate();
            else OnDeactivate();
        }

        if (enabled) {
            ImGui::SameLine();
            ImColor currentColor = CONFIG_COLOR(GetConfigManager(), "Color");
            std::string colorLabel = std::string(LANG("Color")) + "###playerESP";
            if (ImGui::ColorEdit4(
                colorLabel.c_str(),
                reinterpret_cast<float*>(&currentColor.Value),
                colorEditFlags
            ))
            {
                SET_CONFIG_VALUE(GetConfigManager(), "Color", ImColor, currentColor);
            }

            struct BoolOption {
                const char* configKey;
                const char* langKey;
            };

            BoolOption options[] = {
                { "ShowBox", "Show2DBox" },
                { "ShowSkeleton", "ShowSkeleton" },
                { "ShowPlayerSanity", "ShowPlayerSanity" },
                { "ShowDeadStatus", "ShowDeadStatus" },
                { "ShowRoom", "ShowCurrentRoom" },
                { "ShowPrestige", "ShowPrestige" },
                { "ShowExperience", "ShowExperience" },
                { "ShowLevel", "ShowLevel" },
                { "ShowSprinting", "ShowSprinting" }
            };

            for (const auto& opt : options)
            {
                bool value = CONFIG_BOOL(GetConfigManager(), opt.configKey);
                std::string label = std::string(LANG(opt.langKey)) + "###playerESP_" + opt.configKey;
                if (ImGui::Checkbox(label.c_str(), &value))
                    SET_CONFIG_VALUE(GetConfigManager(), opt.configKey, bool, value);
            }
        }
    }
    catch (const std::exception& e) {
        LOG_ERROR("Error in PlayerESP::OnMenu: " + std::string(e.what()));
        ImGui::Text("%s", LANG("ErrorLoadingSettings"));
    }
}

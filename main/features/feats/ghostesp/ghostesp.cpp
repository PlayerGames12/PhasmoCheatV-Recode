#pragma once
#include "ghostesp.h"
#include <vector>
#include <cmath>
#include <chrono>
#define STB_IMAGE_IMPLEMENTATION
#include "imgui/stb_image.h" 

using namespace std::chrono;

using namespace PhasmoCheatV::Features::Visuals;

ID3D11Device* GhostESP::g_pd3dDevice = nullptr;

std::vector<std::pair<SDK::HumanBodyBones, SDK::HumanBodyBones>> mainConnections = {
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

std::vector<SDK::HumanBodyBones> mainBones = {
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

GhostESP::GhostESP() : FeatureCore(LANG("GhostESP_Header"), TYPE_VISUALS)
{
    DECLARE_CONFIG(GetConfigManager(), "ESPColor", ImColor, ImColor(255, 0, 0, 255));
    DECLARE_CONFIG(GetConfigManager(), "BoxType", int, 0);
    DECLARE_CONFIG(GetConfigManager(), "BoxThickness", float, 1.5f);
    DECLARE_CONFIG(GetConfigManager(), "ShowSkeleton", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "SkeletonColor", ImColor, ImColor(255, 255, 255, 255));
    DECLARE_CONFIG(GetConfigManager(), "NameCol", ImColor, ImColor(255, 255, 255, 255));
    DECLARE_CONFIG(GetConfigManager(), "SkeletonThickness", float, 1.0f);
    DECLARE_CONFIG(GetConfigManager(), "ShowPhotoESP", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "ShowBoxESP", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "PhotoESPType", int, 0);
    DECLARE_CONFIG(GetConfigManager(), "PhotoWidth", float, 1.0f);
    DECLARE_CONFIG(GetConfigManager(), "PhotoHeight", float, 1.0f);

    LoadAvailablePhotos();
}

void GhostESP::OnRender()
{
    if (!IsActive()) return;
    if (!Utils::GetGhostAI()) return;

    const auto ghostInfo = Utils::GetGhostAI()->Fields.GhostInfo;
    if (!ghostInfo) return;

    const ImColor nameCol = CONFIG_COLOR(GetConfigManager(), "NameCol");

    DrawName(Utils::GetGhostAI(), nameCol);

    if (CONFIG_BOOL(GetConfigManager(), "ShowBoxESP"))
    {
        const ImColor color = CONFIG_COLOR(GetConfigManager(), "ESPColor");
        const float thickness = CONFIG_FLOAT(GetConfigManager(), "BoxThickness");
        const int boxType = CONFIG_INT(GetConfigManager(), "BoxType");

        switch (boxType)
        {
        case 0: Draw2DBox(Utils::GetGhostAI(), color, thickness); break;
        case 1: DrawCornerBox(Utils::GetGhostAI(), color, thickness); break;
        case 2: DrawFilledBox(Utils::GetGhostAI(), color, thickness); break;
        }
    }

    if (CONFIG_BOOL(GetConfigManager(), "ShowSkeleton"))
    {
        DrawSkeleton(Utils::GetGhostAI(),
            CONFIG_COLOR(GetConfigManager(), "SkeletonColor"),
            CONFIG_FLOAT(GetConfigManager(), "SkeletonThickness"));
    }

    if (CONFIG_BOOL(GetConfigManager(), "ShowPhotoESP"))
    {
        DrawPhotoESP(Utils::GetGhostAI());
    }
}

void GhostESP::SetD3D11Device(ID3D11Device* device)
{
    g_pd3dDevice = device;
    if (g_pd3dDevice)
    {
        LOG_INFO("D3D11 device successfully set for Photo ESP");
    }
    else
    {
        LOG_ERROR("Failed to set D3D11 device - device pointer is null");
    }
}

void GhostESP::LoadAvailablePhotos()
{
    availablePhotos.clear();
    std::string imageDir = Utils::GetPhasmoCheatVDirectory() + "/Images";

    if (!std::filesystem::exists(imageDir))
    {
        LOG_WARN("Images directory does not exist: %s", imageDir.c_str());
        return;
    }

    for (const auto& entry : std::filesystem::directory_iterator(imageDir))
    {
        if (entry.is_regular_file() &&
            (entry.path().extension() == ".png" || entry.path().extension() == ".jpg" ||
                entry.path().extension() == ".jpeg" || entry.path().extension() == ".bmp" ||
                entry.path().extension() == ".tga"))
        {
            availablePhotos.push_back(entry.path().filename().string());
        }
    }

    LOG_INFO("Loaded %d available photos", availablePhotos.size());
}

bool GhostESP::LoadTexture(const std::string& filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    auto it = loadedTextures.find(filename);
    if (it != loadedTextures.end())
    {
        *out_srv = it->second.SRV;
        *out_width = it->second.Width;
        *out_height = it->second.Height;
        return true;
    }

    ID3D11Device* device = g_pd3dDevice;

    if (!device)
    {
        LOG_ERROR("D3D11 device is not initialized. Call SetD3D11Device first.");
        return false;
    }

    std::string fullPath = Utils::GetPhasmoCheatVDirectory() + "/Images/" + filename;

    int width, height, channels;
    unsigned char* image_data = stbi_load(fullPath.c_str(), &width, &height, &channels, 4);
    if (!image_data)
    {
        LOG_ERROR("Failed to load image: %s", filename.c_str());
        return false;
    }

    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    ID3D11Texture2D* pTexture = nullptr;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;

    HRESULT hr = device->CreateTexture2D(&desc, &subResource, &pTexture);
    if (FAILED(hr) || !pTexture)
    {
        LOG_ERROR("Failed to create D3D11 texture: 0x%08X", hr);
        stbi_image_free(image_data);
        return false;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;

    hr = device->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    if (FAILED(hr) || !*out_srv)
    {
        LOG_ERROR("Failed to create D3D11 shader resource view: 0x%08X", hr);
        stbi_image_free(image_data);
        return false;
    }

    TextureData textureData;
    textureData.SRV = *out_srv;
    textureData.Width = width;
    textureData.Height = height;
    loadedTextures[filename] = textureData;

    stbi_image_free(image_data);

    LOG_DEBUG("Loaded D3D11 texture: %s (%dx%d)", filename.c_str(), width, height);
    return true;
}

void GhostESP::DrawPhotoESP(const SDK::GhostAI* ghostAI)
{
    if (!ghostAI || !ghostAI->Fields.raycastPoint || !ghostAI->Fields.feetRaycastPoint)
        return;

    int photoType = CONFIG_INT(GetConfigManager(), "PhotoESPType");
    if (photoType < 0 || photoType >= availablePhotos.size())
        return;

    const std::string& selectedPhoto = availablePhotos[photoType];

    ID3D11ShaderResourceView* textureSRV = nullptr;
    int textureWidth = 0, textureHeight = 0;

    if (!LoadTexture(selectedPhoto, &textureSRV, &textureWidth, &textureHeight))
    {
        LOG_ERROR("Failed to load texture for photo ESP: %s", selectedPhoto.c_str());
        return;
    }

    if (!textureSRV)
    {
        LOG_ERROR("Texture SRV is null for: %s", selectedPhoto.c_str());
        return;
    }

    SDK::Vector3 top = Utils::GetPosVec3(ghostAI->Fields.raycastPoint);
    SDK::Vector3 bottom = Utils::GetPosVec3(ghostAI->Fields.feetRaycastPoint);

    SDK::Vector3 topScreen, bottomScreen;
    if (!Utils::WTS(top, topScreen) || !Utils::WTS(bottom, bottomScreen))
        return;

    float height = fabsf(topScreen.Y - bottomScreen.Y);
    float width = height / 2.0f;

    float photoWidthMultiplier = CONFIG_FLOAT(GetConfigManager(), "PhotoWidth");
    float photoHeightMultiplier = CONFIG_FLOAT(GetConfigManager(), "PhotoHeight");

    width = width * photoWidthMultiplier;
    height = height * photoHeightMultiplier;

    float left = bottomScreen.X - width / 2;
    float right = bottomScreen.X + width / 2;
    float imageTop = bottomScreen.Y - height;
    float imageBottom = bottomScreen.Y;

    auto drawList = ImGui::GetBackgroundDrawList();
    drawList->AddImage(
        (void*)textureSRV,
        ImVec2(left, imageTop),
        ImVec2(right, imageBottom),
        ImVec2(0, 0),
        ImVec2(1, 1),
        IM_COL32_WHITE
    );
}

void GhostESP::CleanupTextures()
{
    for (auto& texture : loadedTextures)
    {
        if (texture.second.SRV)
        {
            texture.second.SRV->Release();
            texture.second.SRV = nullptr;
        }
    }
    loadedTextures.clear();
    LOG_INFO("Cleaned up D3D11 textures");
}

void GhostESP::DrawSkeleton(const SDK::GhostAI* ghostAI, const ImColor& color, float thickness)
{
    if (!ghostAI)
    {
        LOG_WARN("GhostESP::DrawSkeleton called with null ghostAI pointer");
        return;
    }

    auto model = ghostAI->Fields.currentModel;
    if (!model)
    {
        LOG_WARN("GhostESP::DrawSkeleton failed to get model");
        return;
    }

    if (!model->Fields.anim) {
        LOG_WARN("GhostESP::DrawSkeleton failed to get animator");
        return;
    }

    auto animator = model->Fields.anim;
    if (!animator)
    {
        LOG_WARN("GhostESP::DrawSkeleton animator pointer is null");
        return;
    }

    auto drawList = ImGui::GetBackgroundDrawList();

    std::unordered_map<SDK::HumanBodyBones, std::pair<SDK::Vector3, bool>> bonePositions;

    for (auto bone : mainBones)
    {
        SDK::Transform* boneTransform = nullptr;

        try
        {
            boneTransform = SDK::Animator_GetBoneTransform(animator, bone, nullptr);
        }
        catch (const std::exception& e)
        {
            LOG_ERROR("Exception caught in Animator_GetBoneTransform for bone %d: %s", static_cast<int>(bone), e.what());
            continue;
        }
        catch (...)
        {
            LOG_ERROR("Unknown exception caught in Animator_GetBoneTransform for bone %d", static_cast<int>(bone));
            continue;
        }

        if (boneTransform)
        {
            SDK::Vector3 worldPos = Utils::GetPosVec3(boneTransform);
            SDK::Vector3 screenPos;
            bool isOnScreen = Utils::WTS(worldPos, screenPos);
            bonePositions[bone] = std::make_pair(worldPos, isOnScreen);
        }
        else
        {

        }
    }

    for (const auto& connection : mainConnections)
    {
        auto fromBone = connection.first;
        auto toBone = connection.second;

        if (bonePositions.find(fromBone) == bonePositions.end() ||
            bonePositions.find(toBone) == bonePositions.end())
        {
            continue;
        }

        const auto& fromData = bonePositions[fromBone];
        const auto& toData = bonePositions[toBone];

        if (fromData.second && toData.second)
        {
            SDK::Vector3 fromScreen, toScreen;
            if (Utils::WTS(fromData.first, fromScreen) &&
                Utils::WTS(toData.first, toScreen))
            {
                if (fromScreen.Z > 0 && toScreen.Z > 0)
                {
                    drawList->AddLine(
                        ImVec2(fromScreen.X, fromScreen.Y),
                        ImVec2(toScreen.X, toScreen.Y),
                        color,
                        thickness
                    );
                }
            }
        }
    }

    for (const auto& bonePair : bonePositions)
    {
        if (bonePair.second.second)
        {
            SDK::Vector3 screenPos;
            if (Utils::WTS(bonePair.second.first, screenPos) &&
                screenPos.Z > 0)
            {
                drawList->AddCircleFilled(
                    ImVec2(screenPos.X, screenPos.Y),
                    thickness * 0.8f,
                    color
                );
            }
        }
    }
}

void GhostESP::Draw2DBox(const SDK::GhostAI* ghostAI, const ImColor& color, float thickness)
{
    if (!ghostAI || !ghostAI->Fields.raycastPoint || !ghostAI->Fields.feetRaycastPoint)
        return;

    SDK::Vector3 top = Utils::GetPosVec3(ghostAI->Fields.raycastPoint);
    SDK::Vector3 bottom = Utils::GetPosVec3(ghostAI->Fields.feetRaycastPoint);

    SDK::Vector3 topScreen, bottomScreen;
    if (!Utils::WTS(top, topScreen) || !Utils::WTS(bottom, bottomScreen))
        return;

    float height = fabsf(topScreen.Y - bottomScreen.Y);
    float width = height / 2.0f;

    ImGui::GetBackgroundDrawList()->AddRect(
        ImVec2(bottomScreen.X - width / 2, topScreen.Y),
        ImVec2(bottomScreen.X + width / 2, bottomScreen.Y),
        color, 0.0f, 0, thickness
    );
}

void GhostESP::DrawCornerBox(const SDK::GhostAI* ghostAI, const ImColor& color, float thickness)
{
    if (!ghostAI || !ghostAI->Fields.raycastPoint || !ghostAI->Fields.feetRaycastPoint)
        return;

    SDK::Vector3 top = Utils::GetPosVec3(ghostAI->Fields.raycastPoint);
    SDK::Vector3 bottom = Utils::GetPosVec3(ghostAI->Fields.feetRaycastPoint);

    SDK::Vector3 topScreen, bottomScreen;
    if (!Utils::WTS(top, topScreen) || !Utils::WTS(bottom, bottomScreen))
        return;

    float height = fabsf(topScreen.Y - bottomScreen.Y);
    float width = height / 2.0f;

    float lineW = width / 3;
    float lineH = height / 3;

    float left = bottomScreen.X - width / 2;
    float right = bottomScreen.X + width / 2;
    float topY = topScreen.Y;
    float bottomY = bottomScreen.Y;

    auto draw = ImGui::GetBackgroundDrawList();

    draw->AddLine(ImVec2(left, topY), ImVec2(left + lineW, topY), color, thickness);
    draw->AddLine(ImVec2(left, topY), ImVec2(left, topY + lineH), color, thickness);

    draw->AddLine(ImVec2(right, topY), ImVec2(right - lineW, topY), color, thickness);
    draw->AddLine(ImVec2(right, topY), ImVec2(right, topY + lineH), color, thickness);

    draw->AddLine(ImVec2(left, bottomY), ImVec2(left + lineW, bottomY), color, thickness);
    draw->AddLine(ImVec2(left, bottomY), ImVec2(left, bottomY - lineH), color, thickness);

    draw->AddLine(ImVec2(right, bottomY), ImVec2(right - lineW, bottomY), color, thickness);
    draw->AddLine(ImVec2(right, bottomY), ImVec2(right, bottomY - lineH), color, thickness);
}

void GhostESP::DrawFilledBox(const SDK::GhostAI* ghostAI, const ImColor& color, float thickness)
{
    if (!ghostAI || !ghostAI->Fields.raycastPoint || !ghostAI->Fields.feetRaycastPoint)
        return;

    SDK::Vector3 top = Utils::GetPosVec3(ghostAI->Fields.raycastPoint);
    SDK::Vector3 bottom = Utils::GetPosVec3(ghostAI->Fields.feetRaycastPoint);

    SDK::Vector3 topScreen, bottomScreen;
    if (!Utils::WTS(top, topScreen) || !Utils::WTS(bottom, bottomScreen))
        return;

    float height = fabsf(topScreen.Y - bottomScreen.Y);
    float width = height / 2.0f;

    ImGui::GetBackgroundDrawList()->AddRectFilled(
        ImVec2(bottomScreen.X - width / 2, topScreen.Y),
        ImVec2(bottomScreen.X + width / 2, bottomScreen.Y),
        ImColor(color.Value.x, color.Value.y, color.Value.z, 0.2f)
    );

    ImGui::GetBackgroundDrawList()->AddRect(
        ImVec2(bottomScreen.X - width / 2, topScreen.Y),
        ImVec2(bottomScreen.X + width / 2, bottomScreen.Y),
        color, 0.0f, 0, thickness
    );
}

void GhostESP::DrawName(const SDK::GhostAI* ghostAI, const ImColor& color)
{
    if (!ghostAI || !ghostAI->Fields.raycastPoint || !ghostAI->Fields.feetRaycastPoint ||
        !ghostAI->Fields.GhostInfo || !ghostAI->Fields.GhostInfo->Fields.GhostTraits.Name)
        return;

    SDK::Vector3 top = Utils::GetPosVec3(ghostAI->Fields.raycastPoint);
    SDK::Vector3 bottom = Utils::GetPosVec3(ghostAI->Fields.feetRaycastPoint);

    SDK::Vector3 topScreen, bottomScreen;
    if (!Utils::WTS(top, topScreen) || !Utils::WTS(bottom, bottomScreen))
        return;

    float centerX = bottomScreen.X;

    std::string nameStr =
        Utils::UnityStrToSysStr(*ghostAI->Fields.GhostInfo->Fields.GhostTraits.Name);
    std::string typeStr =
        Utils::GhostEnumToStr(ghostAI->Fields.GhostInfo->Fields.GhostTraits.GhostType_);

    std::string fullText = typeStr + " • " + nameStr;
    const char* name = fullText.c_str();

    ImVec2 textSize = ImGui::CalcTextSize(name);

    float textX = centerX - textSize.x * 0.5f;
    float textY = topScreen.Y - textSize.y - 2.0f;

    ImGui::GetBackgroundDrawList()->AddText(
        ImVec2(textX, textY),
        color,
        name
    );
}

void GhostESP::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6, 5));

    auto MakeLabel = [](const char* code, const char* id)
        {
            return std::string(LANG(code)) + "##" + id;
        };

    bool enabled = IsActive();
    if (ImGui::Checkbox(LANG("EnableGhostESP"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        enabled ? OnActivate() : OnDeactivate();
    }

    if (!enabled)
    {
        ImGui::PopStyleVar();
        return;
    }

    constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

    ImColor nameColor = CONFIG_COLOR(GetConfigManager(), "NameCol");
    if (ImGui::ColorEdit4(MakeLabel("NameColor", "ghostESP").c_str(),
        reinterpret_cast<float*>(&nameColor.Value), colorEditFlags))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "NameCol", ImColor, nameColor);
    }

    ImGui::Separator();

    bool showBoxESP = CONFIG_BOOL(GetConfigManager(), "ShowBoxESP");
    if (ImGui::Checkbox(MakeLabel("ShowBoxESP", "ghostESP").c_str(), &showBoxESP))
        SET_CONFIG_VALUE(GetConfigManager(), "ShowBoxESP", bool, showBoxESP);

    if (showBoxESP)
    {
        const char* boxTypes[] = { LANG("BoxType2D"), LANG("BoxTypeCorner"), LANG("BoxTypeFilled") };
        int boxType = CONFIG_INT(GetConfigManager(), "BoxType");

        if (ImGui::Combo(MakeLabel("BoxType", "ghostESP").c_str(),
            &boxType, boxTypes, IM_ARRAYSIZE(boxTypes)))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "BoxType", int, boxType);
        }

        ImColor espColor = CONFIG_COLOR(GetConfigManager(), "ESPColor");
        if (ImGui::ColorEdit4(MakeLabel("Color", "ghostESP").c_str(),
            reinterpret_cast<float*>(&espColor.Value), colorEditFlags))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "ESPColor", ImColor, espColor);
        }

        float boxThickness = CONFIG_FLOAT(GetConfigManager(), "BoxThickness");
        if (ImGui::SliderFloat(MakeLabel("BoxThickness", "ghostESP").c_str(),
            &boxThickness, 0.5f, 5.0f))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "BoxThickness", float, boxThickness);
        }
    }

    ImGui::Separator();

    bool showSkeleton = CONFIG_BOOL(GetConfigManager(), "ShowSkeleton");
    if (ImGui::Checkbox(MakeLabel("ShowSkeleton", "ghostESP").c_str(), &showSkeleton))
        SET_CONFIG_VALUE(GetConfigManager(), "ShowSkeleton", bool, showSkeleton);

    if (showSkeleton)
    {
        ImColor skeletonColor = CONFIG_COLOR(GetConfigManager(), "SkeletonColor");
        if (ImGui::ColorEdit4(MakeLabel("SkeletonColor", "ghostESP").c_str(),
            reinterpret_cast<float*>(&skeletonColor.Value), colorEditFlags))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "SkeletonColor", ImColor, skeletonColor);
        }

        float skeletonThickness = CONFIG_FLOAT(GetConfigManager(), "SkeletonThickness");
        if (ImGui::SliderFloat(MakeLabel("SkeletonThickness", "ghostESP").c_str(),
            &skeletonThickness, 0.5f, 3.0f))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "SkeletonThickness", float, skeletonThickness);
        }
    }

    ImGui::Separator();

    bool showPhotoESP = CONFIG_BOOL(GetConfigManager(), "ShowPhotoESP");
    if (ImGui::Checkbox(MakeLabel("ShowPhotoESP", "ghostESP").c_str(), &showPhotoESP))
        SET_CONFIG_VALUE(GetConfigManager(), "ShowPhotoESP", bool, showPhotoESP);

    if (showPhotoESP)
    {
        float photoWidth = CONFIG_FLOAT(GetConfigManager(), "PhotoWidth");
        if (ImGui::SliderFloat(MakeLabel("PhotoWidth", "ghostESP").c_str(),
            &photoWidth, 0.1f, 3.0f, "%.2f"))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "PhotoWidth", float, photoWidth);
        }

        float photoHeight = CONFIG_FLOAT(GetConfigManager(), "PhotoHeight");
        if (ImGui::SliderFloat(MakeLabel("PhotoHeight", "ghostESP").c_str(),
            &photoHeight, 0.1f, 3.0f, "%.2f"))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "PhotoHeight", float, photoHeight);
        }

        if (!availablePhotos.empty())
        {
            std::vector<const char*> photoNames;
            photoNames.reserve(availablePhotos.size());

            for (auto& p : availablePhotos)
                photoNames.push_back(p.c_str());

            int photoType = CONFIG_INT(GetConfigManager(), "PhotoESPType");
            if (ImGui::Combo(MakeLabel("PhotoType", "ghostESP").c_str(),
                &photoType, photoNames.data(), (int)photoNames.size()))
            {
                SET_CONFIG_VALUE(GetConfigManager(), "PhotoESPType", int, photoType);
            }
        }

        if (ImGui::Button(MakeLabel("RefreshImages", "ghostESP").c_str(), ImVec2(140, 24)))
        {
            LoadAvailablePhotos();
        }
    }

    ImGui::PopStyleVar();
}
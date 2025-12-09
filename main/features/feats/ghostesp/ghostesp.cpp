#pragma once
#include "ghostesp.h"
#include <vector>
#include <cmath>
#include <chrono>

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

GhostESP::GhostESP() : FeatureCore("Ghost ESP", TYPE_VISUALS)
{
    DECLARE_CONFIG(GetConfigManager(), "ESPColor", ImColor, ImColor(255, 0, 0, 255));
    DECLARE_CONFIG(GetConfigManager(), "BoxType", int, 0);
    DECLARE_CONFIG(GetConfigManager(), "BoxThickness", float, 1.5f);
    DECLARE_CONFIG(GetConfigManager(), "ShowSkeleton", bool, true);
    DECLARE_CONFIG(GetConfigManager(), "SkeletonColor", ImColor, ImColor(255, 255, 255, 255));
    DECLARE_CONFIG(GetConfigManager(), "SkeletonThickness", float, 1.0f);
    DECLARE_CONFIG(GetConfigManager(), "ShowPhotoESP", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "PhotoESPType", int, 0);
    DECLARE_CONFIG(GetConfigManager(), "PhotoWidth", float, 1.0f);
    DECLARE_CONFIG(GetConfigManager(), "PhotoHeight", float, 1.0f);

    //LoadAvailablePhotos();
}

void GhostESP::OnRender()
{
    if (!IsActive()) return;
    if (!InGame::ghostAI) return;

    const auto ghostInfo = InGame::ghostAI->Fields.GhostInfo;
    if (!ghostInfo) return;

    const ImColor color = CONFIG_COLOR(GetConfigManager(), "ESPColor");
    const float thickness = CONFIG_FLOAT(GetConfigManager(), "BoxThickness");
    const int boxType = CONFIG_INT(GetConfigManager(), "BoxType");

    switch (boxType)
    {
    case 0: Draw2DBox(InGame::ghostAI, color, thickness); break;
    case 1: Draw3DBox(InGame::ghostAI, color, thickness); break;
    case 2: DrawCornerBox(InGame::ghostAI, color, thickness); break;
    case 3: DrawCircle(InGame::ghostAI, color, thickness); break;
    case 4: DrawFilledBox(InGame::ghostAI, color, thickness); break;
    case 5: DrawCross(InGame::ghostAI, color, thickness); break;
    case 6: DrawDiamond(InGame::ghostAI, color, thickness); break;
    case 7: DrawTriangle(InGame::ghostAI, color, thickness); break;
    case 8: DrawArrow(InGame::ghostAI, color, thickness); break;
    case 9: DrawNone(InGame::ghostAI, color, thickness); break;
    }

    if (CONFIG_BOOL(GetConfigManager(), "ShowSkeleton"))
    {
        DrawSkeleton(InGame::ghostAI,
            CONFIG_COLOR(GetConfigManager(), "SkeletonColor"),
            CONFIG_FLOAT(GetConfigManager(), "SkeletonThickness"));
    }

    //if (CONFIG_BOOL(GetConfigManager(), "ShowPhotoESP"))
    //{
    //    DrawPhotoESP(InGame::ghostAI);
    //}
}

// ====================== Photo ESP Methods ======================
/*
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

    int photoType = std::get<int>(PhotoESPTypeSetting->GetValue());
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

    float photoWidthMultiplier = std::get<float>(PhotoWidthSetting->GetValue());
    float photoHeightMultiplier = std::get<float>(PhotoHeightSetting->GetValue());

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
}*/

// ====================== SKELETON ESP ======================
void GhostESP::DrawSkeleton(const SDK::GhostAI* ghostAI, const ImColor& color, float thickness)
{
    if (!ghostAI)
    {
        LOG_WARN("GhostESP::DrawSkeleton called with null ghostAI pointer");
        return;
    }

    auto model = ghostAI->Fields.NormalModel;
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

// ====================== 2D BOX ======================
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

// ====================== 3D BOX ======================
void GhostESP::Draw3DBox(const SDK::GhostAI* ghostAI, const ImColor& color, float thickness)
{
    if (!ghostAI || !ghostAI->Fields.raycastPoint || !ghostAI->Fields.feetRaycastPoint)
        return;

    SDK::Vector3 top = Utils::GetPosVec3(ghostAI->Fields.raycastPoint);
    SDK::Vector3 bottom = Utils::GetPosVec3(ghostAI->Fields.feetRaycastPoint);

    float height = top.Y - bottom.Y;
    float width = height / 2.0f;
    float depth = width / 2.0f;

    std::vector<SDK::Vector3> points = {
        {bottom.X - width, bottom.Y, bottom.Z - depth},
        {bottom.X + width, bottom.Y, bottom.Z - depth},
        {bottom.X + width, bottom.Y, bottom.Z + depth},
        {bottom.X - width, bottom.Y, bottom.Z + depth},

        {top.X - width, top.Y, top.Z - depth},
        {top.X + width, top.Y, top.Z - depth},
        {top.X + width, top.Y, top.Z + depth},
        {top.X - width, top.Y, top.Z + depth},
    };

    std::vector<ImVec2> screenPoints;
    for (auto& p : points)
    {
        SDK::Vector3 sp;
        if (!Utils::WTS(p, sp)) return;
        screenPoints.emplace_back(sp.X, sp.Y);
    }

    auto draw = ImGui::GetBackgroundDrawList();

    draw->AddLine(screenPoints[0], screenPoints[1], color, thickness);
    draw->AddLine(screenPoints[1], screenPoints[2], color, thickness);
    draw->AddLine(screenPoints[2], screenPoints[3], color, thickness);
    draw->AddLine(screenPoints[3], screenPoints[0], color, thickness);

    draw->AddLine(screenPoints[4], screenPoints[5], color, thickness);
    draw->AddLine(screenPoints[5], screenPoints[6], color, thickness);
    draw->AddLine(screenPoints[6], screenPoints[7], color, thickness);
    draw->AddLine(screenPoints[7], screenPoints[4], color, thickness);

    draw->AddLine(screenPoints[0], screenPoints[4], color, thickness);
    draw->AddLine(screenPoints[1], screenPoints[5], color, thickness);
    draw->AddLine(screenPoints[2], screenPoints[6], color, thickness);
    draw->AddLine(screenPoints[3], screenPoints[7], color, thickness);
}

// ====================== CORNER BOX ======================
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

// ====================== CIRCLE ======================
void GhostESP::DrawCircle(const SDK::GhostAI* ghostAI, const ImColor& color, float thickness)
{
    if (!ghostAI || !ghostAI->Fields.huntingRaycastPoint)
        return;

    SDK::Vector3 center = Utils::GetPosVec3(ghostAI->Fields.huntingRaycastPoint);
    SDK::Vector3 screenPos;
    if (!Utils::WTS(center, screenPos))
        return;

    ImGui::GetBackgroundDrawList()->AddCircle(
        ImVec2(screenPos.X, screenPos.Y),
        40.0f,
        color,
        40,
        thickness
    );
}

// ====================== FILLED BOX ======================
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

// ====================== CROSS ======================
void GhostESP::DrawCross(const SDK::GhostAI* ghostAI, const ImColor& color, float thickness)
{
    if (!ghostAI || !ghostAI->Fields.huntingRaycastPoint)
        return;

    SDK::Vector3 center = Utils::GetPosVec3(ghostAI->Fields.huntingRaycastPoint);
    SDK::Vector3 screenPos;
    if (!Utils::WTS(center, screenPos))
        return;

    float size = 20.0f;
    auto draw = ImGui::GetBackgroundDrawList();

    draw->AddLine(
        ImVec2(screenPos.X - size, screenPos.Y),
        ImVec2(screenPos.X + size, screenPos.Y),
        color, thickness
    );

    draw->AddLine(
        ImVec2(screenPos.X, screenPos.Y - size),
        ImVec2(screenPos.X, screenPos.Y + size),
        color, thickness
    );
}

// ====================== DIAMOND ======================
void GhostESP::DrawDiamond(const SDK::GhostAI* ghostAI, const ImColor& color, float thickness)
{
    if (!ghostAI || !ghostAI->Fields.huntingRaycastPoint)
        return;

    SDK::Vector3 center = Utils::GetPosVec3(ghostAI->Fields.huntingRaycastPoint);
    SDK::Vector3 screenPos;
    if (!Utils::WTS(center, screenPos))
        return;

    float size = 25.0f;
    auto draw = ImGui::GetBackgroundDrawList();

    draw->AddLine(
        ImVec2(screenPos.X, screenPos.Y - size),
        ImVec2(screenPos.X + size, screenPos.Y),
        color, thickness
    );

    draw->AddLine(
        ImVec2(screenPos.X + size, screenPos.Y),
        ImVec2(screenPos.X, screenPos.Y + size),
        color, thickness
    );

    draw->AddLine(
        ImVec2(screenPos.X, screenPos.Y + size),
        ImVec2(screenPos.X - size, screenPos.Y),
        color, thickness
    );

    draw->AddLine(
        ImVec2(screenPos.X - size, screenPos.Y),
        ImVec2(screenPos.X, screenPos.Y - size),
        color, thickness
    );
}

// ====================== TRIANGLE ======================
void GhostESP::DrawTriangle(const SDK::GhostAI* ghostAI, const ImColor& color, float thickness)
{
    if (!ghostAI || !ghostAI->Fields.raycastPoint || !ghostAI->Fields.feetRaycastPoint)
        return;

    SDK::Vector3 top = Utils::GetPosVec3(ghostAI->Fields.raycastPoint);
    SDK::Vector3 bottom = Utils::GetPosVec3(ghostAI->Fields.feetRaycastPoint);

    SDK::Vector3 topScreen, bottomScreen;
    if (!Utils::WTS(top, topScreen) || !Utils::WTS(bottom, bottomScreen))
        return;

    float width = fabsf(topScreen.Y - bottomScreen.Y) / 2.0f;
    auto draw = ImGui::GetBackgroundDrawList();

    draw->AddLine(
        ImVec2(bottomScreen.X, topScreen.Y),
        ImVec2(bottomScreen.X + width, bottomScreen.Y),
        color, thickness
    );

    draw->AddLine(
        ImVec2(bottomScreen.X + width, bottomScreen.Y),
        ImVec2(bottomScreen.X - width, bottomScreen.Y),
        color, thickness
    );

    draw->AddLine(
        ImVec2(bottomScreen.X - width, bottomScreen.Y),
        ImVec2(bottomScreen.X, topScreen.Y),
        color, thickness
    );
}

// ====================== ARROW ======================
void GhostESP::DrawArrow(const SDK::GhostAI* ghostAI, const ImColor& color, float thickness)
{
    if (!ghostAI || !ghostAI->Fields.huntingRaycastPoint)
        return;

    SDK::Vector3 center = Utils::GetPosVec3(ghostAI->Fields.huntingRaycastPoint);
    SDK::Vector3 screenPos;
    if (!Utils::WTS(center, screenPos))
        return;

    float size = 30.0f;
    auto draw = ImGui::GetBackgroundDrawList();

    draw->AddLine(
        ImVec2(screenPos.X, screenPos.Y - size),
        ImVec2(screenPos.X, screenPos.Y + size),
        color, thickness
    );

    draw->AddLine(
        ImVec2(screenPos.X, screenPos.Y - size),
        ImVec2(screenPos.X - size / 2, screenPos.Y - size / 2),
        color, thickness
    );

    draw->AddLine(
        ImVec2(screenPos.X, screenPos.Y - size),
        ImVec2(screenPos.X + size / 2, screenPos.Y - size / 2),
        color, thickness
    );
}

void GhostESP::DrawNone(const SDK::GhostAI* ghostAI, const ImColor& color, float thickness)
{
    if (!ghostAI || !ghostAI->Fields.huntingRaycastPoint)
        return;
}

// ====================== MENU ======================
void GhostESP::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox("Enable Ghost ESP", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled) {
        constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

        ImColor espColor = CONFIG_COLOR(GetConfigManager(), "ESPColor");
        if (ImGui::ColorEdit4("Color##ghostESP", reinterpret_cast<float*>(&espColor.Value), colorEditFlags))
            SET_CONFIG_VALUE(GetConfigManager(), "ESPColor", ImColor, espColor);

        const char* boxTypes[] = {
            "2D Box", "3D Box", "Corner Box", "Circle",
            "Filled Box", "Cross", "Diamond", "Triangle", "Arrow", "None"
        };
        int boxType = CONFIG_INT(GetConfigManager(), "BoxType");
        if (ImGui::Combo("Box Type##ghostESP", &boxType, boxTypes, IM_ARRAYSIZE(boxTypes)))
            SET_CONFIG_VALUE(GetConfigManager(), "BoxType", int, boxType);

        float boxThickness = CONFIG_FLOAT(GetConfigManager(), "BoxThickness");
        if (ImGui::SliderFloat("Box Thickness##ghostESP", &boxThickness, 0.5f, 5.0f))
            SET_CONFIG_VALUE(GetConfigManager(), "BoxThickness", float, boxThickness);

        ImGui::Separator();

        bool showSkeleton = CONFIG_BOOL(GetConfigManager(), "ShowSkeleton");
        if (ImGui::Checkbox("Show Skeleton##ghostESP", &showSkeleton))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowSkeleton", bool, showSkeleton);

        if (showSkeleton) {
            ImColor skeletonColor = CONFIG_COLOR(GetConfigManager(), "SkeletonColor");
            if (ImGui::ColorEdit4("Skeleton Color##ghostESP", reinterpret_cast<float*>(&skeletonColor.Value), colorEditFlags))
                SET_CONFIG_VALUE(GetConfigManager(), "SkeletonColor", ImColor, skeletonColor);

            float skeletonThickness = CONFIG_FLOAT(GetConfigManager(), "SkeletonThickness");
            if (ImGui::SliderFloat("Skeleton Thickness##ghostESP", &skeletonThickness, 0.5f, 3.0f))
                SET_CONFIG_VALUE(GetConfigManager(), "SkeletonThickness", float, skeletonThickness);
        }

        ImGui::Separator();

        bool showPhotoESP = CONFIG_BOOL(GetConfigManager(), "ShowPhotoESP");
        if (ImGui::Checkbox("Show Photo ESP##ghostESP", &showPhotoESP))
            SET_CONFIG_VALUE(GetConfigManager(), "ShowPhotoESP", bool, showPhotoESP);

        if (showPhotoESP) {
            float photoWidth = CONFIG_FLOAT(GetConfigManager(), "PhotoWidth");
            if (ImGui::SliderFloat("Photo Width##ghostESP", &photoWidth, 0.1f, 3.0f, "%.2f"))
                SET_CONFIG_VALUE(GetConfigManager(), "PhotoWidth", float, photoWidth);

            float photoHeight = CONFIG_FLOAT(GetConfigManager(), "PhotoHeight");
            if (ImGui::SliderFloat("Photo Height##ghostESP", &photoHeight, 0.1f, 3.0f, "%.2f"))
                SET_CONFIG_VALUE(GetConfigManager(), "PhotoHeight", float, photoHeight);

            if (ImGui::Button("Reset Photo Size##ghostESP", ImVec2(120, 25))) {
                SET_CONFIG_VALUE(GetConfigManager(), "PhotoWidth", float, 1.0f);
                SET_CONFIG_VALUE(GetConfigManager(), "PhotoHeight", float, 1.0f);
            }
            ImGui::SameLine();
            ImGui::Text("Default: 1.0 x 1.0");
        }
        /*
        if (!availablePhotos.empty()) {
            std::vector<const char*> photoNames;
            for (const auto& photo : availablePhotos) {
                photoNames.push_back(photo.c_str());
            }

            int photoType = CONFIG_INT(GetConfigManager(), "PhotoESPType");
            if (ImGui::Combo("Photo Type##ghostESP", &photoType, photoNames.data(), photoNames.size()))
                SET_CONFIG_VALUE(GetConfigManager(), "PhotoESPType", int, photoType);

            if (ImGui::Button("Refresh Images##ghostESP")) {
                LoadAvailablePhotos();
            }
        }
        else {
            ImGui::Text("No images found in Images folder");
            if (ImGui::Button("Refresh Images##ghostESP")) {
                LoadAvailablePhotos();
            }
        }
        */
    }

    ImGui::PopStyleVar();
}
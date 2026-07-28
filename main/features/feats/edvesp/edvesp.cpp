#include "edvesp.h"

#include "imgui/stb_image.h"

#include "images/uv_default.h"
#include "images/uv_obake.h"

#include "images/mirror.h"
#include "images/music_box.h"
#include "images/summoningCircle.h"
#include "images/monkey_paw.h"
#include "images/tarotCard.h"
#include "images/voodooDoll.h"
#include "images/ouijaBoard.h"

#include "images/emf.h"

using namespace PhasmoCheatV::Features::Visuals;

static ID3D11ShaderResourceView* g_uvDefaultSRV = nullptr;
static ID3D11ShaderResourceView* g_uvObakeSRV = nullptr;

static ID3D11ShaderResourceView* g_mirrorSRV = nullptr;
static ID3D11ShaderResourceView* g_musicBoxSRV = nullptr;
static ID3D11ShaderResourceView* g_summoningCircleSRV = nullptr;
static ID3D11ShaderResourceView* g_monkeyPawSRV = nullptr;
static ID3D11ShaderResourceView* g_tarotCardSRV = nullptr;
static ID3D11ShaderResourceView* g_voodooDollSRV = nullptr;
static ID3D11ShaderResourceView* g_ouijaBoardSRV = nullptr;

static ID3D11ShaderResourceView* g_emfSRV = nullptr;

static int g_texW = 0;
static int g_texH = 0;

static bool g_loaded = false;

static std::string GetCursedIconFallback()
{
    return "C";
}

EvidenceESP::EvidenceESP() : FeatureCore(LANG("EvidenceESP_Header"), TYPE_VISUALS)
{
    DECLARE_CONFIG(GetConfigManager(), "DNAEvidenceShow", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "CursedItemShow", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "GhostOrbShow", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "EMFShow", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "OtherEvidenceShow", bool, false);

    DECLARE_CONFIG(GetConfigManager(), "DNAEvidenceColor", ImColor, ImColor(1.f, 1.f, 1.f, 1.f));
    DECLARE_CONFIG(GetConfigManager(), "CursedItemColor", ImColor, ImColor(1.f, 1.f, 1.f, 1.f));
    DECLARE_CONFIG(GetConfigManager(), "GhostOrbColor", ImColor, ImColor(1.f, 1.f, 1.f, 1.f));
    DECLARE_CONFIG(GetConfigManager(), "EMFColor", ImColor, ImColor(1.f, 1.f, 1.f, 1.f));
    DECLARE_CONFIG(GetConfigManager(), "OtherEvidenceColor", ImColor, ImColor(1.f, 1.f, 1.f, 1.f));

    DECLARE_CONFIG(GetConfigManager(), "UseNewIcons", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "IconSize", float, 1.0f);
}

bool EvidenceESP::LoadFromMemory(
    unsigned char* data,
    size_t size,
    ID3D11ShaderResourceView** out_srv,
    int* w,
    int* h)
{
    int width, height, channels;

    unsigned char* image = stbi_load_from_memory(
        data,
        (int)size,
        &width,
        &height,
        &channels,
        4);

    if (!image)
        return false;

    D3D11_TEXTURE2D_DESC desc{};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA sub{};
    sub.pSysMem = image;
    sub.SysMemPitch = width * 4;

    ID3D11Texture2D* tex = nullptr;

    if (FAILED(renderer->Device->CreateTexture2D(
        &desc,
        &sub,
        &tex)))
    {
        stbi_image_free(image);
        return false;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
    srvDesc.Format = desc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    if (FAILED(renderer->Device->CreateShaderResourceView(
        tex,
        &srvDesc,
        out_srv)))
    {
        tex->Release();
        stbi_image_free(image);
        return false;
    }

    tex->Release();
    stbi_image_free(image);

    *w = width;
    *h = height;

    return true;
}

void EvidenceESP::LoadTextures()
{
    if (g_loaded)
        return;

    LoadFromMemory(
        uvdefault,
        sizeof(uvdefault),
        &g_uvDefaultSRV,
        &g_texW,
        &g_texH);

    LoadFromMemory(
        uvobake,
        sizeof(uvobake),
        &g_uvObakeSRV,
        &g_texW,
        &g_texH);

    LoadFromMemory(
        mirror,
        sizeof(mirror),
        &g_mirrorSRV,
        &g_texW,
        &g_texH);

    LoadFromMemory(
        musicbox,
        sizeof(musicbox),
        &g_musicBoxSRV,
        &g_texW,
        &g_texH);

    LoadFromMemory(
        summoningCircle,
        sizeof(summoningCircle),
        &g_summoningCircleSRV,
        &g_texW,
        &g_texH);

    LoadFromMemory(
        monkeypaw,
        sizeof(monkeypaw),
        &g_monkeyPawSRV,
        &g_texW,
        &g_texH);

    LoadFromMemory(
        tarotCard,
        sizeof(tarotCard),
        &g_tarotCardSRV,
        &g_texW,
        &g_texH);

    LoadFromMemory(
        voodooDoll,
        sizeof(voodooDoll),
        &g_voodooDollSRV,
        &g_texW,
        &g_texH);

    LoadFromMemory(
        ouijaBoard,
        sizeof(ouijaBoard),
        &g_ouijaBoardSRV,
        &g_texW,
        &g_texH);

    LoadFromMemory(
        emf,
        sizeof(emf),
        &g_emfSRV,
        &g_texW,
        &g_texH);

    g_loaded = true;
}

ID3D11ShaderResourceView* EvidenceESP::GetEvidenceTexture(
    SDK::EvidenceType type)
{
    switch (type)
    {
    case SDK::EvidenceType::hauntedMirror:
        return g_mirrorSRV;

    case SDK::EvidenceType::musicBox:
        return g_musicBoxSRV;

    case SDK::EvidenceType::summoningCicle:
        return g_summoningCircleSRV;

    case SDK::EvidenceType::monkeyPaw:
        return g_monkeyPawSRV;

    case SDK::EvidenceType::tarotCards:
        return g_tarotCardSRV;

    case SDK::EvidenceType::voodooDoll:
        return g_voodooDollSRV;

    case SDK::EvidenceType::ouijaBoard:
        return g_ouijaBoardSRV;

    case SDK::EvidenceType::fingerprint:
        return g_uvDefaultSRV;

    case SDK::EvidenceType::obakeFingerprint:
        return g_uvObakeSRV;

    case SDK::EvidenceType::footstep:
        return g_uvDefaultSRV;

    default:
        return nullptr;
    }
}

void EvidenceESP::DrawTextureIcon(
    const SDK::Vector3& screenPos,
    ID3D11ShaderResourceView* tex,
    ImColor color)
{
    if (!tex)
        return;

    float scale =
        CONFIG_FLOAT(GetConfigManager(), "IconSize");

    float size = 32.f * scale;

    ImGui::GetBackgroundDrawList()->AddImage(
        (void*)tex,
        ImVec2(screenPos.X, screenPos.Y),
        ImVec2(screenPos.X + size, screenPos.Y + size),
        ImVec2(0, 0),
        ImVec2(1, 1),
        color);
}

void EvidenceESP::DrawIconText(
    const SDK::Vector3& screenPos,
    const std::string& icon,
    const std::string& text,
    ImColor color)
{
    auto draw = ImGui::GetBackgroundDrawList();

    ImFont* normalFont = ImGui::GetFont();
    ImFont* iconFont = normalFont;

    auto& fonts = ImGui::GetIO().Fonts->Fonts;

    if (fonts.size() > 6 && fonts[6])
        iconFont = fonts[6];

    float normalFontSize = ImGui::GetFontSize();

    float iconScale =
        CONFIG_FLOAT(GetConfigManager(), "IconSize", 1.0f);

    float iconFontSize = normalFontSize * iconScale;

    std::string leftBracket = "[";
    std::string rightBracket = "] ";

    float leftWidth =
        normalFont->CalcTextSizeA(
            normalFontSize,
            FLT_MAX,
            0.0f,
            leftBracket.c_str()).x;

    float iconWidth =
        iconFont->CalcTextSizeA(
            iconFontSize,
            FLT_MAX,
            0.0f,
            icon.c_str()).x;

    float rightWidth =
        normalFont->CalcTextSizeA(
            normalFontSize,
            FLT_MAX,
            0.0f,
            rightBracket.c_str()).x;

    draw->AddText(
        normalFont,
        normalFontSize,
        ImVec2(screenPos.X, screenPos.Y),
        color,
        leftBracket.c_str());

    draw->AddText(
        iconFont,
        iconFontSize,
        ImVec2(screenPos.X + leftWidth, screenPos.Y),
        color,
        icon.c_str());

    draw->AddText(
        normalFont,
        normalFontSize,
        ImVec2(screenPos.X + leftWidth + iconWidth, screenPos.Y),
        color,
        rightBracket.c_str());

    if (!text.empty())
    {
        draw->AddText(
            normalFont,
            normalFontSize,
            ImVec2(
                screenPos.X + leftWidth + iconWidth + rightWidth,
                screenPos.Y),
            color,
            text.c_str());
    }
}

void EvidenceESP::RenderEMF()
{
    if (!CONFIG_BOOL(GetConfigManager(), "EMFShow"))
        return;

    LoadTextures();

    if (!SDK::EMFData_sFields->instance)
        return;

    auto emfSpots = SDK::EMFData_sFields->instance->Fields.EMFSpots;

    if (!emfSpots)
        return;

    auto items =
        emfSpots->Fields.Items;

    if (!items)
        return;

    const bool useNewIcons =
        CONFIG_BOOL(GetConfigManager(), "UseNewIcons");

    ImColor color =
        CONFIG_COLOR(GetConfigManager(), "EMFColor");

    auto draw =
        ImGui::GetBackgroundDrawList();

    for (int i = 0; i < emfSpots->Fields.Size; i++)
    {
        auto emfSpot =
            items->Vector[i];

        if (!emfSpot)
            continue;

        auto transform =
            SDK::Component_Get_Transform(
                reinterpret_cast<SDK::Component*>(emfSpot),
                nullptr);

        if (!transform)
            continue;

        SDK::Vector3 worldPos =
            SDK::Transform_Get_Position(
                transform,
                nullptr);

        SDK::Vector3 screenPos;

        if (!Utils::WTS(worldPos, screenPos))
            continue;

        int level = emfSpot->Fields.strenght + 1;

        if (useNewIcons && g_emfSRV)
        {
            float scale =
                CONFIG_FLOAT(
                    GetConfigManager(),
                    "IconSize");

            float size =
                32.f * scale;

            draw->AddImage(
                (void*)g_emfSRV,
                ImVec2(
                    screenPos.X,
                    screenPos.Y),
                ImVec2(
                    screenPos.X + size,
                    screenPos.Y + size),
                ImVec2(0, 0),
                ImVec2(1, 1),
                color);

            std::string text =
                "EMF " + std::to_string(level);

            draw->AddText(
                ImVec2(
                    screenPos.X + size + 4.f,
                    screenPos.Y + (size / 4.f)),
                color,
                text.c_str());
        }
        else
        {
            DrawIconText(
                screenPos,
                "V",
                "EMF " + std::to_string(level),
                color);
        }
    }
}

void EvidenceESP::RenderEvidence()
{
    LoadTextures();

    if (!SDK::EvidenceController_sFields->instance)
        return;

    const bool cursedItemEnabled =
        CONFIG_BOOL(GetConfigManager(), "CursedItemShow");

    const bool dnaEvidenceEnabled =
        CONFIG_BOOL(GetConfigManager(), "DNAEvidenceShow");

    const bool otherEvidenceEnabled =
        CONFIG_BOOL(GetConfigManager(), "OtherEvidenceShow");

    const bool ghostOrbEnabled =
        CONFIG_BOOL(GetConfigManager(), "GhostOrbShow");

    const bool useNewIcons =
        CONFIG_BOOL(GetConfigManager(), "UseNewIcons");

    const auto evidenceList =
        SDK::EvidenceController_sFields->instance->Fields.EvidenceList;

    if (!evidenceList)
        return;

    if (!evidenceList->Fields.Items)
        return;

    if (evidenceList->Fields.Size <= 0)
        return;

    auto items =
        evidenceList->Fields.Items->Vector;

    for (int i = 0; i < evidenceList->Fields.Size; i++)
    {
        auto evidence = items[i];

        if (!evidence)
            continue;

        if (!evidence->Fields.MediaValues)
            continue;

        auto evidenceType =
            evidence->Fields.MediaValues->Fields.EvidenceType;

        bool isCursedItem =
            Utils::IsCursedItem(evidenceType);

        bool isDNA =
            evidenceType == SDK::EvidenceType::DNA;

        bool isGhostOrb =
            evidenceType == SDK::EvidenceType::ghostOrb;

        bool isEMF =
            evidenceType == SDK::EvidenceType::emfSpot;

        bool isUV =
            evidenceType == SDK::EvidenceType::fingerprint ||
            evidenceType == SDK::EvidenceType::obakeFingerprint ||
            evidenceType == SDK::EvidenceType::footstep;

        bool isOther =
            !isCursedItem &&
            !isDNA &&
            !isGhostOrb &&
            !isEMF &&
            !isUV;

        bool shouldDraw = false;

        ImColor color;

        if (isCursedItem && cursedItemEnabled)
        {
            shouldDraw = true;

            color = CONFIG_COLOR(
                GetConfigManager(),
                "CursedItemColor");
        }
        else if (isDNA && dnaEvidenceEnabled)
        {
            shouldDraw = true;

            color = CONFIG_COLOR(
                GetConfigManager(),
                "DNAEvidenceColor");
        }
        else if (isGhostOrb && ghostOrbEnabled)
        {
            shouldDraw = true;

            color = CONFIG_COLOR(
                GetConfigManager(),
                "GhostOrbColor");
        }
        else if ((isOther || isUV) && otherEvidenceEnabled)
        {
            shouldDraw = true;

            color = CONFIG_COLOR(
                GetConfigManager(),
                "OtherEvidenceColor");
        }

        if (!shouldDraw)
            continue;

        SDK::Vector3 worldPos =
            Utils::GetPosVec3(
                reinterpret_cast<SDK::Component*>(evidence));

        SDK::Vector3 screenPos;

        if (!Utils::WTS(worldPos, screenPos))
            continue;

        if (useNewIcons)
        {
            ID3D11ShaderResourceView* tex =
                GetEvidenceTexture(evidenceType);

            if (tex)
            {
                ImColor drawColor = color;

                if (evidenceType == SDK::EvidenceType::monkeyPaw)
                {
                    drawColor = ImColor(
                        255,
                        255,
                        255,
                        (int)(color.Value.w * 255.f));
                }

                DrawTextureIcon(
                    screenPos,
                    tex,
                    drawColor);

                continue;
            }
        }

        if (isDNA)
        {
            auto draw = ImGui::GetBackgroundDrawList();

            ImFont* iconFont = ImGui::GetFont();

            auto& fonts = ImGui::GetIO().Fonts->Fonts;

            if (fonts.size() > 6 && fonts[6])
                iconFont = fonts[6];

            float iconScale =
                CONFIG_FLOAT(GetConfigManager(), "IconSize", 1.0f);

            float iconFontSize =
                ImGui::GetFontSize() * iconScale;

            draw->AddText(
                iconFont,
                iconFontSize,
                ImVec2(screenPos.X, screenPos.Y),
                color,
                "B");

            continue;
        }

        std::string icon = "M";

        if (isCursedItem)
            icon = "C";
        else if (isGhostOrb)
            icon = "O";

        DrawIconText(
            screenPos,
            icon,
            Utils::GhostEnumToStr(evidenceType),
            color);
    }
}

void EvidenceESP::OnRender()
{
    if (!IsActive())
        return;

    RenderEMF();
    RenderEvidence();
}

void EvidenceESP::OnMenuRender()
{
    constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

    auto MakeLabel = [](const char* code, const char* id) -> std::string
        {
            return std::string(LANG(code)) + "##" + id;
        };

    bool enabled = IsActive();
    bool cursedItemEnabled = CONFIG_BOOL(GetConfigManager(), "CursedItemShow");
    bool dnaEvidenceEnabled = CONFIG_BOOL(GetConfigManager(), "DNAEvidenceShow");
    bool ghostOrbEnabled = CONFIG_BOOL(GetConfigManager(), "GhostOrbShow");
    bool emfEnabled = CONFIG_BOOL(GetConfigManager(), "EMFShow");
    bool otherEvidenceEnabled = CONFIG_BOOL(GetConfigManager(), "OtherEvidenceShow");
    bool useNewIcons = CONFIG_BOOL(GetConfigManager(), "UseNewIcons");

    ImColor cursedItemColor = CONFIG_COLOR(GetConfigManager(), "CursedItemColor");
    ImColor dnaEvidenceColor = CONFIG_COLOR(GetConfigManager(), "DNAEvidenceColor");
    ImColor ghostOrbColor = CONFIG_COLOR(GetConfigManager(), "GhostOrbColor");
    ImColor emfColor = CONFIG_COLOR(GetConfigManager(), "EMFColor");
    ImColor otherEvidenceColor = CONFIG_COLOR(GetConfigManager(), "OtherEvidenceColor");

    if (ImGui::Checkbox(LANG("EnableEvidenceESP"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        enabled ? OnActivate() : OnDeactivate();
    }

    if (!enabled)
        return;

    if (ImGui::Checkbox(LANG("CursedItem"), &cursedItemEnabled))
        SET_CONFIG_VALUE(GetConfigManager(), "CursedItemShow", bool, cursedItemEnabled);

    ImGui::SameLine();
    if (ImGui::ColorEdit4(
        MakeLabel("Color", "cursed").c_str(),
        reinterpret_cast<float*>(&cursedItemColor.Value),
        colorEditFlags))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "CursedItemColor", ImColor, cursedItemColor);
    }

    if (ImGui::Checkbox(LANG("DNAEvidence"), &dnaEvidenceEnabled))
        SET_CONFIG_VALUE(GetConfigManager(), "DNAEvidenceShow", bool, dnaEvidenceEnabled);

    ImGui::SameLine();
    if (ImGui::ColorEdit4(
        MakeLabel("Color", "dna").c_str(),
        reinterpret_cast<float*>(&dnaEvidenceColor.Value),
        colorEditFlags))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "DNAEvidenceColor", ImColor, dnaEvidenceColor);
    }

    if (ImGui::Checkbox(LANG("EMFSpots"), &emfEnabled))
        SET_CONFIG_VALUE(GetConfigManager(), "EMFShow", bool, emfEnabled);

    ImGui::SameLine();
    if (ImGui::ColorEdit4(
        MakeLabel("Color", "emf").c_str(),
        reinterpret_cast<float*>(&emfColor.Value),
        colorEditFlags))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "EMFColor", ImColor, emfColor);
    }

    if (ImGui::Checkbox(LANG("GhostOrb"), &ghostOrbEnabled))
        SET_CONFIG_VALUE(GetConfigManager(), "GhostOrbShow", bool, ghostOrbEnabled);

    ImGui::SameLine();
    if (ImGui::ColorEdit4(
        MakeLabel("Color", "ghostOrb").c_str(),
        reinterpret_cast<float*>(&ghostOrbColor.Value),
        colorEditFlags))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "GhostOrbColor", ImColor, ghostOrbColor);
    }

    if (ImGui::Checkbox(LANG("OtherEvidence"), &otherEvidenceEnabled))
        SET_CONFIG_VALUE(GetConfigManager(), "OtherEvidenceShow", bool, otherEvidenceEnabled);

    ImGui::SameLine();
    if (ImGui::ColorEdit4(
        MakeLabel("Color", "other").c_str(),
        reinterpret_cast<float*>(&otherEvidenceColor.Value),
        colorEditFlags))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "OtherEvidenceColor", ImColor, otherEvidenceColor);
    }

    if (ImGui::Checkbox(LANG("UseNewIcons"), &useNewIcons))
        SET_CONFIG_VALUE(GetConfigManager(), "UseNewIcons", bool, useNewIcons);

    float iconSize = CONFIG_FLOAT(GetConfigManager(), "IconSize");

    if (ImGui::SliderFloat(LANG("IconSize"), &iconSize, 0.5f, 2.5f))
        SET_CONFIG_VALUE(GetConfigManager(), "IconSize", float, iconSize);
}
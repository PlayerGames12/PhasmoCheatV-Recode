#include "showmic.h"
#include "imgui/stb_image.h"
#include "images/mic_on.h"
#include "images/mic_off.h"

using namespace PhasmoCheatV::Features::Visuals;

ShowMicro::ShowMicro() : FeatureCore(LANG("ShowMicro_Header"), TYPE_VISUALS) 
{
	DECLARE_CONFIG(GetConfigManager(), "scale", float, 1.f);
    DECLARE_CONFIG(GetConfigManager(), "MicroOnColor", ImColor, ImColor(0, 255, 0, 255));
}

bool ShowMicro::LoadFromMemory(unsigned char* data, size_t size,
    ID3D11ShaderResourceView** out_srv, int* w, int* h)
{
    int width, height, channels;

    unsigned char* image = stbi_load_from_memory(
        data, (int)size, &width, &height, &channels, 4);

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

    if (FAILED(renderer->Device->CreateTexture2D(&desc, &sub, &tex)))
    {
        stbi_image_free(image);
        return false;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
    srvDesc.Format = desc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    if (FAILED(renderer->Device->CreateShaderResourceView(tex, &srvDesc, out_srv)))
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

void ShowMicro::OnRender()
{
    if (!IsActive())
        return;

    if (!texturesLoaded)
    {
        LoadFromMemory(micon, sizeof(micon), &micOnSRV, &micW, &micH);
        LoadFromMemory(micoff, sizeof(micoff), &micOffSRV, &micW, &micH);
        texturesLoaded = true;
    }

    auto* localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer) return;

    auto* fieldsLocalPlayer = localPlayer->Fields.LocalPlayer;
    if (!fieldsLocalPlayer) return;

    auto* voice = fieldsLocalPlayer->Fields.voice;
    if (!voice) return;

    auto* playerVoice = voice->Fields.playerVoice;
    if (!playerVoice) return;

    bool micState = playerVoice->Fields.isMicrophoneActive;

    ID3D11ShaderResourceView* tex = micState ? micOnSRV : micOffSRV;
    if (!tex) return;

    ImVec2 screen = ImGui::GetIO().DisplaySize;

    float padding = 10.0f;
    float scale = CONFIG_FLOAT(GetConfigManager(), "scale");

    float w = micW * scale;
    float h = micH * scale;

    float x = padding;
    float y = screen.y - h - padding;

    ImU32 tint = IM_COL32_WHITE;

    if (micState)
    {
        ImColor col = CONFIG_COLOR(GetConfigManager(), "MicroOnColor");
        tint = col;
    }

    ImGui::GetBackgroundDrawList()->AddImage(
        (void*)tex,
        ImVec2(x, y),
        ImVec2(x + w, y + h),
        ImVec2(0, 0),
        ImVec2(1, 1),
        tint
    );
}

void ShowMicro::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox(LANG("ShowMicroEnable"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        enabled ? OnActivate() : OnDeactivate();
    }

    if (enabled)
    {
        float scale = CONFIG_FLOAT(GetConfigManager(), "scale");
        if (ImGui::SliderFloat(LANG("MicroScale"), &scale, 0.5f, 5.0f, "%.2f"))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "scale", float, scale);
        }

        ImColor col = CONFIG_COLOR(GetConfigManager(), "MicroOnColor");
        if (ImGui::ColorEdit4(LANG("MicroOnColor"),
            reinterpret_cast<float*>(&col.Value),
            ImGuiColorEditFlags_NoInputs))
        {
            SET_CONFIG_VALUE(GetConfigManager(), "MicroOnColor", ImColor, col);
        }
    }

    ImGui::PopStyleVar();
}
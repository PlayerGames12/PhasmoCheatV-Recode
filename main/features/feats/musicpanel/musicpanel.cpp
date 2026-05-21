#include "musicpanel.h"

using namespace PhasmoCheatV::Features::Visuals;
namespace WMC = winrt::Windows::Media::Control;
namespace WS = winrt::Windows::Storage::Streams;

MusicPanel::MusicPanel() : FeatureCore(LANG("MusicPanel_Header"), TYPE_VISUALS)
{
    DECLARE_CONFIG(GetConfigManager(), "showOnlyMenu", bool, false);
    winrt::init_apartment(winrt::apartment_type::multi_threaded);
}

ID3D11Device* MusicPanel::GetDevice()
{
    if (!m_device && renderer)
        m_device = renderer->Device;

    return m_device;
}

MusicPanel::GSMTCSession MusicPanel::GetSession()
{
    if (!m_manager)
        m_manager = GSMTCManager::RequestAsync().get();

    auto current = m_manager.GetCurrentSession();

    if (!current)
    {
        auto sessions = m_manager.GetSessions();
        if (sessions.Size() > 0)
            current = sessions.GetAt(0);
    }

    m_session = current;
    return m_session;
}

void MusicPanel::UpdateMedia()
{
    double now = ImGui::GetTime();
    if (now - m_lastUpdate < 0.5)
        return;

    m_lastUpdate = now;

    try
    {
        auto session = GetSession();
        if (!session) return;

        auto props = session.TryGetMediaPropertiesAsync().get();
        if (!props) return;

        std::wstring newTitle = props.Title().c_str();
        std::wstring newArtist = props.Artist().c_str();

        bool changed = (newTitle != m_state.title) || (newArtist != m_state.artist);

        m_state.title = newTitle;
        m_state.artist = newArtist;

        auto tl = session.GetTimelineProperties();

        auto start = tl.StartTime().count();
        auto end = tl.EndTime().count();
        auto pos = tl.Position().count();

        m_state.position = pos - start;
        m_state.duration = (end > start) ? (end - start) : 1;

        if (changed)
        {
            m_state.cover.Reset();

            auto thumb = props.Thumbnail();
            if (thumb)
            {
                using namespace winrt::Windows::Storage::Streams;

                auto stream = thumb.OpenReadAsync().get();
                auto size = stream.Size();

                WS::Buffer buffer((uint32_t)size);
                stream.ReadAsync(buffer, buffer.Capacity(), WS::InputStreamOptions::None).get();

                m_state.cover = LoadTextureFromMemory(buffer.data(), (int)size);
            }
        }
    }
    catch (...) {}
}

void MusicPanel::PlayPause()
{
    auto s = GetSession();
    if (s) s.TryTogglePlayPauseAsync();
}

void MusicPanel::Next()
{
    auto s = GetSession();
    if (s) s.TrySkipNextAsync();
}

void MusicPanel::Prev()
{
    auto s = GetSession();
    if (s) s.TrySkipPreviousAsync();
}

std::string MusicPanel::WideToUtf8(const std::wstring& w)
{
    if (w.empty()) return {};

    int size = WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string str(size, 0);

    WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), str.data(), size, nullptr, nullptr);
    return str;
}

std::string MusicPanel::FormatTime(int64_t ticks)
{
    int sec = (int)(ticks / 10000000);
    int m = sec / 60;
    int s = sec % 60;

    char buf[32];
    sprintf_s(buf, "%02d:%02d", m, s);
    return buf;
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>
MusicPanel::LoadTextureFromMemory(unsigned char* data, int size)
{
    int w, h, channels;
    unsigned char* image = stbi_load_from_memory(data, size, &w, &h, &channels, 4);
    if (!image) return nullptr;

    ID3D11Device* device = GetDevice();
    if (!device)
    {
        stbi_image_free(image);
        return nullptr;
    }

    D3D11_TEXTURE2D_DESC desc{};
    desc.Width = w;
    desc.Height = h;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA sub{};
    sub.pSysMem = image;
    sub.SysMemPitch = w * 4;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
    if (FAILED(device->CreateTexture2D(&desc, &sub, tex.GetAddressOf())))
    {
        stbi_image_free(image);
        return nullptr;
    }

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
    if (FAILED(device->CreateShaderResourceView(tex.Get(), nullptr, srv.GetAddressOf())))
    {
        stbi_image_free(image);
        return nullptr;
    }

    stbi_image_free(image);
    return srv;
}

void MusicPanel::OnRender()
{
    if (!IsActive()) return;
	if (CONFIG_BOOL(GetConfigManager(), "showOnlyMenu") && !menu.Open) return;

    UpdateMedia();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6, 6));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 2));

    ImGui::SetNextWindowSize(ImVec2(308, 140), ImGuiCond_Once);
    ImGui::Begin("###MusicPanel", nullptr,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse);

    ImVec2 coverSize(64, 64);

    if (m_state.cover)
        ImGui::Image((void*)m_state.cover.Get(), coverSize);
    else
        ImGui::Dummy(coverSize);

    ImGui::SameLine();
    ImGui::BeginGroup();

    ImGui::TextUnformatted(WideToUtf8(m_state.title).c_str());
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f),
        "%s", WideToUtf8(m_state.artist).c_str());

    std::string cur = FormatTime(m_state.position);
    std::string dur = FormatTime(m_state.duration);

    ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f),
        "%s / %s", cur.c_str(), dur.c_str());

    ImGui::EndGroup();

    float spacing = ImGui::GetStyle().ItemSpacing.x;
    float available = ImGui::GetContentRegionAvail().x;
    float btnW = (available - spacing * 2.0f) / 3.0f;

    if (btnW < 50.0f) btnW = 50.0f;

    ImGui::Spacing();

    std::string playText =
        m_session &&
        m_session.GetPlaybackInfo().PlaybackStatus() ==
        winrt::Windows::Media::Control::
        GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing
        ? "Pause" : "Play";

    if (ImGui::Button("<<", ImVec2(btnW, 29))) Prev();
    ImGui::SameLine();
    if (ImGui::Button(playText.c_str(), ImVec2(btnW, 29))) PlayPause();
    ImGui::SameLine();
    if (ImGui::Button(">>", ImVec2(btnW, 29))) Next();

    ImGui::End();

    ImGui::PopStyleVar(2);
}

void MusicPanel::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox(LANG("MusicPanelEnable"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        enabled ? OnActivate() : OnDeactivate();
    }

    if (enabled)
    {
		bool showOnlyMenu = CONFIG_BOOL(GetConfigManager(), "showOnlyMenu");
        if (ImGui::Checkbox(LANG("ShowOnlyMenu"), &showOnlyMenu))
            SET_CONFIG_VALUE(GetConfigManager(), "showOnlyMenu", bool, showOnlyMenu);
    }

    ImGui::PopStyleVar();
}
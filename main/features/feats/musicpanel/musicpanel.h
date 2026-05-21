#pragma once
#include "../Includes.h"
#include "imgui/stb_image.h"
#include <winrt/base.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Media.Control.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace PhasmoCheatV::Features::Visuals
{
    class MusicPanel : public FeatureCore
    {
    public:
        MusicPanel();
        ~MusicPanel() override = default;

        void OnActivate() override {}
        void OnDeactivate() override {}
        void OnRender() override;
        void OnMenuRender() override;

    private:
        using GSMTCManager = winrt::Windows::Media::Control::GlobalSystemMediaTransportControlsSessionManager;
        using GSMTCSession = winrt::Windows::Media::Control::GlobalSystemMediaTransportControlsSession;

        struct MediaState
        {
            std::wstring title;
            std::wstring artist;
            int64_t position = 0;
            int64_t duration = 1;
            Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> cover;
        };

    private:
        ID3D11Device* m_device = nullptr;
        GSMTCManager m_manager{ nullptr };
        GSMTCSession m_session{ nullptr };

        MediaState m_state{};
        double m_lastUpdate = 0.0;

        ID3D11Device* GetDevice();
        GSMTCSession GetSession();
        void UpdateMedia();

        void PlayPause();
        void Next();
        void Prev();

        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>
            LoadTextureFromMemory(unsigned char* data, int size);

        std::string WideToUtf8(const std::wstring& w);
        std::string FormatTime(int64_t ticks);
    };
}
#pragma once
// I take this blur code from https://yougame.biz/threads/372949/#post-3472394 (noad)

#include <d3d11.h>
#include <dxgi.h>
#include "../Includes.h"
#include "pshader.h"

inline ImVec2 operator/(const ImVec2& a, const ImVec2& b) { return { a.x / b.x, a.y / b.y }; }

inline ID3D11Device* g_Device = nullptr;
inline ID3D11DeviceContext* g_Context = nullptr;
inline IDXGISwapChain* g_Swapchain = nullptr;

inline ID3D11Texture2D* g_BackBufferTex = nullptr;
inline ID3D11ShaderResourceView* g_BackBufferSRV = nullptr;
inline ID3D11PixelShader* g_BlurPS = nullptr;

inline void dx_release(IUnknown*& res)
{
    if (res) { res->Release(); res = nullptr; }
}

inline void dx_blur_init(IDXGISwapChain* sc, ID3D11Device* dev, ID3D11DeviceContext* ctx)
{
    g_Swapchain = sc;
    g_Device = dev;
    g_Context = ctx;

    if (!g_Device || !g_Context || !g_Swapchain)
        return;

    // shader
    if (!g_BlurPS)
        g_Device->CreatePixelShader(pshaderd, sizeof(pshaderd), nullptr, &g_BlurPS);

    // backbuffer copy texture
    if (!g_BackBufferTex)
    {
        ID3D11Texture2D* back = nullptr;
        g_Swapchain->GetBuffer(0, IID_PPV_ARGS(&back));

        D3D11_TEXTURE2D_DESC desc;
        back->GetDesc(&desc);
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;

        g_Device->CreateTexture2D(&desc, nullptr, &g_BackBufferTex);

        D3D11_SHADER_RESOURCE_VIEW_DESC srv{};
        srv.Format = desc.Format;
        srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srv.Texture2D.MipLevels = 1;

        g_Device->CreateShaderResourceView(g_BackBufferTex, &srv, &g_BackBufferSRV);

        dx_release(reinterpret_cast<IUnknown*&>(back));
    }
}

inline void dx_blur_update()
{
    if (!g_BackBufferTex || !g_Swapchain) return;

    ID3D11Texture2D* back = nullptr;
    g_Swapchain->GetBuffer(0, IID_PPV_ARGS(&back));

    g_Context->CopyResource(g_BackBufferTex, back);

    dx_release(reinterpret_cast<IUnknown*&>(back));
}

inline void dx_blur_draw(ImDrawList* dl, ImVec2 min, ImVec2 max, float rounding = 0.f)
{
    if (!g_BackBufferSRV || !g_BlurPS)
        return;

    ImVec2 screen = ImGui::GetIO().DisplaySize;

    ImVec2 uv0 = min / screen;
    ImVec2 uv1 = max / screen;

    // bind shader
    dl->AddCallback([](const ImDrawList*, const ImDrawCmd*)
        {
            g_Context->PSSetShader(g_BlurPS, nullptr, 0);
        }, nullptr);

    // draw blurred image
    dl->AddImage(
        g_BackBufferSRV,
        min,
        max,
        uv0,
        uv1,
        IM_COL32(255, 255, 255, 100)
    );

    // restore state
    dl->AddCallback(ImDrawCallback_ResetRenderState, nullptr);
}
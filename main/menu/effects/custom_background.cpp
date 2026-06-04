#include "custom_background.h"
#include "imgui/stb_image.h"
#include <filesystem>
#include <algorithm>
#include <windows.h>
#include "../styles.h"

namespace fs = std::filesystem;

namespace CustomBackground
{
    static std::vector<ImageEntry> g_entries;
    static bool g_initialized = false;

    static std::string GetImagesDir()
    {
        std::string base = Utils::GetPhasmoCheatVDirectory();
        std::string dir = base + "\\Images";

        try { fs::create_directories(dir); }
        catch (...) {}

        return dir;
    }

    static bool IsSupported(const std::string& ext)
    {
        std::string e = ext;
        std::transform(e.begin(), e.end(), e.begin(), ::tolower);
        return e == ".png" || e == ".jpg" || e == ".jpeg" ||
            e == ".bmp" || e == ".tga" || e == ".gif";
    }

    static void ReleaseEntry(ImageEntry& e)
    {
        if (e.srv) { e.srv->Release(); e.srv = nullptr; }
        e.w = e.h = 0;
    }

    void RefreshFileList()
    {
        for (auto& e : g_entries) ReleaseEntry(e);
        g_entries.clear();

        std::string dir = GetImagesDir();
        try
        {
            for (auto& p : fs::directory_iterator(dir))
            {
                if (!p.is_regular_file()) continue;
                std::string ext = p.path().extension().string();
                if (!IsSupported(ext)) continue;

                ImageEntry e;
                e.filename = p.path().filename().string();
                e.fullPath = p.path().string();
                g_entries.push_back(std::move(e));
            }
        }
        catch (...) {}

        std::sort(g_entries.begin(), g_entries.end(),
            [](const ImageEntry& a, const ImageEntry& b) { return a.filename < b.filename; });

        g_initialized = true;
    }

    void Shutdown()
    {
        for (auto& e : g_entries) ReleaseEntry(e);
        g_entries.clear();
        g_initialized = false;
    }

    static bool LoadFromFile(ImageEntry& e)
    {
        if (e.srv) return true;

        int w, h, ch;
        unsigned char* image = stbi_load(e.fullPath.c_str(), &w, &h, &ch, 4);
        if (!image) return false;

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

        if (FAILED(renderer->Device->CreateShaderResourceView(tex, &srvDesc, &e.srv)))
        {
            tex->Release();
            stbi_image_free(image);
            return false;
        }

        tex->Release();
        stbi_image_free(image);

        e.w = w;
        e.h = h;
        return true;
    }

    static ImageEntry* GetSelected()
    {
        if (SelectedFile.empty()) return nullptr;
        for (auto& e : g_entries)
            if (e.filename == SelectedFile) return &e;
        return nullptr;
    }

    const std::vector<ImageEntry>& GetEntries() { return g_entries; }

    void Draw(ImDrawList* dl, const ImVec2& pos, const ImVec2& size, float rounding)
    {
        if (!Enabled) return;
        if (!g_initialized) RefreshFileList();

        ImageEntry* e = GetSelected();
        if (!e) return;
        if (!LoadFromFile(*e)) return;
        if (!e->srv) return;

        if (Mode == DrawMode::Replace)
        {
            dl->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y),
                IM_COL32(10, 10, 14, 255), rounding);
        }

        int alpha = (int)(std::clamp(Opacity, 0.f, 1.f) * 255.f);
        ImU32 tint = IM_COL32(255, 255, 255, alpha);

        ImVec2 areaMin = ImVec2(pos.x + Offset.x, pos.y + Offset.y);
        ImVec2 areaMax = ImVec2(pos.x + size.x + Offset.x, pos.y + size.y + Offset.y);

        float iw = (float)e->w;
        float ih = (float)e->h;
        float aw = size.x;
        float ah = size.y;

        dl->PushClipRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), true);

        auto drawImage = [&](ImVec2 a, ImVec2 b, ImVec2 uvA = ImVec2(0, 0), ImVec2 uvB = ImVec2(1, 1))
            {
                if (rounding > 0.f && Mode == DrawMode::Replace)
                    dl->AddImageRounded((void*)e->srv, a, b, uvA, uvB, tint, rounding);
                else
                    dl->AddImage((void*)e->srv, a, b, uvA, uvB, tint);
            };

        switch (Scale)
        {
        case ScaleMode::Stretch:
        {
            drawImage(areaMin, areaMax);
            break;
        }
        case ScaleMode::Fit:
        {
            float sx = aw / iw;
            float sy = ah / ih;
            float s = std::min<float>(sx, sy) * UserScale;
            float dw = iw * s;
            float dh = ih * s;
            ImVec2 a(areaMin.x + (aw - dw) * 0.5f, areaMin.y + (ah - dh) * 0.5f);
            ImVec2 b(a.x + dw, a.y + dh);
            drawImage(a, b);
            break;
        }
        case ScaleMode::Fill:
        {
            float sx = aw / iw;
            float sy = ah / ih;
            float s = std::max<float>(sx, sy) * UserScale;
            float dw = iw * s;
            float dh = ih * s;
            ImVec2 a(areaMin.x + (aw - dw) * 0.5f, areaMin.y + (ah - dh) * 0.5f);
            ImVec2 b(a.x + dw, a.y + dh);
            drawImage(a, b);
            break;
        }
        case ScaleMode::Center:
        {
            float dw = iw * UserScale;
            float dh = ih * UserScale;
            ImVec2 a(areaMin.x + (aw - dw) * 0.5f, areaMin.y + (ah - dh) * 0.5f);
            ImVec2 b(a.x + dw, a.y + dh);
            drawImage(a, b);
            break;
        }
        case ScaleMode::Tile:
        {
            float dw = iw * UserScale;
            float dh = ih * UserScale;
            if (dw < 4.f) dw = 4.f;
            if (dh < 4.f) dh = 4.f;

            for (float y = areaMin.y; y < areaMax.y; y += dh)
            {
                for (float x = areaMin.x; x < areaMax.x; x += dw)
                {
                    ImVec2 a(x, y);
                    ImVec2 b(x + dw, y + dh);
                    drawImage(a, b);
                }
            }
            break;
        }
        }

        dl->PopClipRect();
    }

    void DrawSettingsUI(float dpiScale)
    {
        if (!g_initialized) RefreshFileList();

        ImGui::PushID("CustomBg");

        if (ImGui::Checkbox(LANG("CustomBackground"), &Enabled)) { SetMenuDefaultStyle(); }

        if (ImGui::Button(LANG("Refresh")))
            RefreshFileList();

        ImGui::SameLine();
        if (ImGui::Button(LANG("OpenFolder")))
        {
            std::string dir = GetImagesDir();
            ShellExecuteA(nullptr, "open", dir.c_str(), nullptr, nullptr, SW_SHOW);
        }

        if (!Enabled) { ImGui::PopID(); return; }

        ImGui::SetNextItemWidth(220 * dpiScale);
        if (ImGui::BeginCombo(LANG("Image"), SelectedFile.empty() ? LANG("None") : SelectedFile.c_str()))
        {
            if (ImGui::Selectable(LANG("None"), SelectedFile.empty()))
                SelectedFile.clear();

            for (auto& e : g_entries)
            {
                bool selected = (e.filename == SelectedFile);
                if (ImGui::Selectable(e.filename.c_str(), selected))
                    SelectedFile = e.filename;
                if (selected) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        const char* modes[] =
        {
            LANG("OverlayBackground"),
            LANG("ReplaceBackground")
        };

        int m = (int)Mode;
        ImGui::SetNextItemWidth(220 * dpiScale);
        if (ImGui::Combo(LANG("DrawMode"), &m, modes, IM_ARRAYSIZE(modes)))
            Mode = (DrawMode)m;

        const char* scales[] =
        {
            LANG("Stretch"),
            LANG("Fit"),
            LANG("Fill"),
            LANG("Center"),
            LANG("Tile")
        };

        int s = (int)Scale;
        ImGui::SetNextItemWidth(220 * dpiScale);
        if (ImGui::Combo(LANG("Scale"), &s, scales, IM_ARRAYSIZE(scales)))
            Scale = (ScaleMode)s;

        ImGui::SliderFloat(LANG("Opacity"), &Opacity, 0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat(LANG("UserScale"), &UserScale, 0.1f, 4.0f, "%.2f");
        ImGui::SliderFloat2(LANG("Offset"), (float*)&Offset, -500.0f, 500.0f, "%.0f");

        ImGui::PopID();
    }
}
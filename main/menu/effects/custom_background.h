#pragma once
#include <string>
#include <vector>
#include <d3d11.h>
#include "../Includes.h"

namespace CustomBackground
{
    enum class DrawMode : int
    {
        Overlay = 0,
        Replace = 1
    };

    enum class ScaleMode : int
    {
        Stretch = 0,
        Fit = 1,
        Fill = 2,
        Center = 3,
        Tile = 4 
    };

    struct ImageEntry
    {
        std::string filename;
        std::string fullPath;
        ID3D11ShaderResourceView* srv = nullptr;
        int w = 0, h = 0;
    };

    inline bool        Enabled = false;
    inline std::string SelectedFile = "";
    inline DrawMode    Mode = DrawMode::Overlay;
    inline ScaleMode   Scale = ScaleMode::Fill;
    inline float       Opacity = 1.0f;
    inline ImVec2      Offset = ImVec2(0, 0);
    inline float       UserScale = 1.0f;

    void RefreshFileList();
    void Shutdown();
    void Draw(ImDrawList* dl, const ImVec2& pos, const ImVec2& size, float rounding);
    void DrawSettingsUI(float dpiScale);
    const std::vector<ImageEntry>& GetEntries();
}
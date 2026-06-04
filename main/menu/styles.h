#pragma once
#include "../includes.h"
#include "../res/fonts/DefFont.hpp"
#include "../res/fonts/HeadFont.hpp"
#include "../res/fonts/VCustomFont.hpp"
#include "effects/custom_background.h"

using namespace PhasmoCheatV;

inline void SetMenuDefaultStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(0, 0);
    style.FramePadding = ImVec2(12, 8);
    style.ItemSpacing = ImVec2(8, 6);
    style.ItemInnerSpacing = ImVec2(6, 6);
    style.IndentSpacing = 20;
    style.ScrollbarSize = 10;
    style.GrabMinSize = 10;

    style.WindowBorderSize = 0;
    style.ChildBorderSize = 0;
    style.PopupBorderSize = 0;
    style.FrameBorderSize = 0;
    style.TabBorderSize = 0;

    style.WindowRounding = 14;
    style.ChildRounding = 12;
    style.FrameRounding = 8;
    style.PopupRounding = 10;
    style.ScrollbarRounding = 6;
    style.GrabRounding = 6;
    style.TabRounding = 0;

    ImVec4* colors = style.Colors;

    colors[ImGuiCol_WindowBg] = darkBg;
    bool transparentChildren = Globals::IsMenuBlur
        || (CustomBackground::Enabled && !CustomBackground::SelectedFile.empty());
    if (transparentChildren) colors[ImGuiCol_ChildBg] = ImVec4(0, 0, 0, 0);
    else                     colors[ImGuiCol_ChildBg] = darkerBg;
    colors[ImGuiCol_FrameBg] = cardBg;
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.18f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.22f, 0.22f, 0.24f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    colors[ImGuiCol_Button] = accentPurpleDark;
    colors[ImGuiCol_ButtonHovered] = accentPurple;
    colors[ImGuiCol_ButtonActive] = accentPurpleLight;

    colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

    colors[ImGuiCol_Header] = accentPurpleDark;
    colors[ImGuiCol_HeaderHovered] = accentPurple;
    colors[ImGuiCol_HeaderActive] = accentPurpleLight;

    colors[ImGuiCol_Tab] = darkerBg;
    colors[ImGuiCol_TabHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TabActive] = darkBg;
    colors[ImGuiCol_TabUnfocused] = darkerBg;
    colors[ImGuiCol_TabUnfocusedActive] = darkBg;

    colors[ImGuiCol_TitleBg] = darkerBg;
    colors[ImGuiCol_TitleBgActive] = darkerBg;
    colors[ImGuiCol_CheckMark] = accentPurple;
    colors[ImGuiCol_SliderGrab] = accentPurple;
    colors[ImGuiCol_SliderGrabActive] = accentPurpleLight;
    colors[ImGuiCol_TextSelectedBg] = ImVec4(accentPurple.x, accentPurple.y, accentPurple.z, 0.35f);
    colors[ImGuiCol_SeparatorHovered] = accentPurple;
    colors[ImGuiCol_SeparatorActive] = accentPurpleLight;
    colors[ImGuiCol_ResizeGrip] = accentPurpleDark;
    colors[ImGuiCol_ResizeGripHovered] = accentPurple;
    colors[ImGuiCol_ResizeGripActive] = accentPurpleLight;
}

inline void InitFonts()
{
    ImGuiIO& io = ImGui::GetIO();

    ImFontConfig fontConfig;
    bool isChinese = LanguageManager::GetCurrentLanguage() == Language::ZH;

    // 0
    g_FontMain = io.Fonts->AddFontFromMemoryCompressedTTF(
        DefFont_compressed_data,
        DefFont_compressed_size,
        19.f,
        &fontConfig
    );

    // 1
    io.Fonts->AddFontFromMemoryCompressedTTF(
        HeadFont_compressed_data,
        HeadFont_compressed_size,
        20.f,
        &fontConfig
    );
    // 2
    io.Fonts->AddFontFromMemoryCompressedTTF(
        VCustom_compressed_data,
        VCustom_compressed_size,
        35.f,
        &fontConfig
    );
    // 3
    io.Fonts->AddFontFromMemoryCompressedTTF(
        DefFont_compressed_data,
        DefFont_compressed_size,
        40.f,
        &fontConfig
    );
    // 4
    io.Fonts->AddFontFromMemoryCompressedTTF(
        DefFont_compressed_data,
        DefFont_compressed_size,
        25.f,
        &fontConfig
    );
    // 5
    io.Fonts->AddFontFromMemoryCompressedTTF(
        VCustom_compressed_data,
        VCustom_compressed_size,
        20.f,
        &fontConfig
    );
    // 6
    io.Fonts->AddFontFromMemoryCompressedTTF(
        VCustom_compressed_data,
        VCustom_compressed_size,
        15.f,
        &fontConfig
    );
    // 7
    io.Fonts->AddFontFromMemoryCompressedTTF(
        DefFont_compressed_data,
        DefFont_compressed_size,
        20.f,
        &fontConfig
    );
    //8
    io.Fonts->AddFontFromMemoryCompressedTTF(
        VCustom_compressed_data,
        VCustom_compressed_size,
        120.f,
        &fontConfig
    );
    // 9
    io.Fonts->AddFontFromMemoryCompressedTTF(
        VCustom_compressed_data,
        VCustom_compressed_size,
        50.f,
        &fontConfig
    );
    // 10
    std::string cnPath = "C:\\Windows\\Fonts\\msyh.ttc";
    if (std::filesystem::exists(cnPath))
    {
        g_FontChinese = io.Fonts->AddFontFromFileTTF(
            cnPath.c_str(),
            18.f,
            &fontConfig,
            io.Fonts->GetGlyphRangesChineseFull()
        );

        g_FontChineseReady = (g_FontChinese != nullptr);
    }
    else
    {
        g_FontChinese = g_FontMain;
        g_FontChineseReady = false;
    }
}
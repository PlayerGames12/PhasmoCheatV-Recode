#pragma once
#include <vector>
#include <cstdlib>
#include <cmath>
#include "../Includes.h"

// idk author, sorry

#ifndef FIREFLY_COUNT
#define FIREFLY_COUNT 60
#endif

namespace ImGuiFireflies
{
    struct Fly
    {
        ImVec2 pos;
        ImVec2 vel;
        float  phase;
        float  speed;
        float  size;
        float  hueShift;
    };

    inline std::vector<Fly>& Flies() { static std::vector<Fly> s; return s; }
    inline bool& Initialized() { static bool v = false; return v; }
    inline ImVec2& LastSize() { static ImVec2 v(-1.f, -1.f); return v; }

    inline void Spawn(Fly& f, float w, float h)
    {
        f.pos = ImVec2((float)(std::rand() % (int)w), (float)(std::rand() % (int)h));
        float ang = (std::rand() % 628) / 100.f;
        float spd = 8.f + (std::rand() % 20);
        f.vel = ImVec2(std::cosf(ang) * spd, std::sinf(ang) * spd);
        f.phase = (std::rand() % 628) / 100.f;
        f.speed = 0.8f + (std::rand() % 200) / 100.f;
        f.size = 1.5f + (std::rand() % 250) / 100.f;
        f.hueShift = (std::rand() % 60) / 255.f;
    }
}

inline void Fireflies()
{
    using namespace ImGuiFireflies;

    ImGuiWindow* win = ImGui::GetCurrentWindow();
    if (!win || win->SkipItems) return;

    ImVec2 screen = ImGui::GetIO().DisplaySize;
    float w = screen.x, h = screen.y;
    if (w <= 5.f || h <= 5.f) return;

    if (!Initialized()) { std::srand((unsigned)std::time(nullptr)); Initialized() = true; }

    bool size_changed = LastSize().x < 0.f
        || std::fabs(LastSize().x - w) > 1.f
        || std::fabs(LastSize().y - h) > 1.f;

    if (size_changed)
    {
        LastSize() = ImVec2(w, h);
        Flies().clear();
        Flies().reserve(FIREFLY_COUNT);
        for (int i = 0; i < FIREFLY_COUNT; ++i)
        {
            Fly f{}; Spawn(f, w, h); Flies().push_back(f);
        }
    }

    float dt = ImGui::GetIO().DeltaTime;
    if (dt <= 0.f) dt = 1.f / 60.f;
    if (dt > 0.05f) dt = 0.05f;

    ImDrawList* dl = ImGui::GetBackgroundDrawList();

    for (auto& f : Flies())
    {
        f.vel.x += ((std::rand() % 100) - 50) * dt * 0.5f;
        f.vel.y += ((std::rand() % 100) - 50) * dt * 0.5f;

        float sp = std::sqrtf(f.vel.x * f.vel.x + f.vel.y * f.vel.y);
        const float maxSp = 30.f;
        if (sp > maxSp) { f.vel.x = f.vel.x / sp * maxSp; f.vel.y = f.vel.y / sp * maxSp; }

        f.pos.x += f.vel.x * dt;
        f.pos.y += f.vel.y * dt;

        if (f.pos.x < -10) f.pos.x = w + 10;
        if (f.pos.x > w + 10) f.pos.x = -10;
        if (f.pos.y < -10) f.pos.y = h + 10;
        if (f.pos.y > h + 10) f.pos.y = -10;

        f.phase += f.speed * dt;
        float glow = 0.5f + 0.5f * std::sinf(f.phase);

        int a = (int)(glow * 220.f);
        int aOut = (int)(glow * 60.f);
        ImU32 core = IM_COL32(255, 230 + (int)(f.hueShift * 255) % 25, 130, a);
        ImU32 halo = IM_COL32(255, 200, 100, aOut);

        dl->AddCircleFilled(f.pos, f.size * 4.0f, halo & 0x10FFFFFF, 16);
        dl->AddCircleFilled(f.pos, f.size * 2.0f, halo, 16);
        dl->AddCircleFilled(f.pos, f.size, core, 16);
    }
}
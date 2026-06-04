#pragma once
#include <vector>
#include <cmath>
#include "../Includes.h"

#ifndef PETAL_COUNT
#define PETAL_COUNT 50
#endif

namespace ImGuiPetals
{
    struct Petal
    {
        ImVec2 pos;
        float  vx, vy;
        float  rot;
        float  rotSpeed;
        float  size;
        float  sway;
        float  swayPhase;
        float  alpha;
    };

    inline std::vector<Petal>& List() { static std::vector<Petal> s; return s; }
    inline bool& Initialized() { static bool v = false; return v; }
    inline ImVec2& LastSize() { static ImVec2 v(-1.f, -1.f); return v; }

    inline void Spawn(Petal& p, float w, float h, bool randomY = false)
    {
        p.pos.x = (float)(std::rand() % (int)w);
        p.pos.y = randomY ? (float)(std::rand() % (int)h) : -20.f;
        p.vx = -10.f + (std::rand() % 30);
        p.vy = 30.f + (std::rand() % 50);
        p.rot = (std::rand() % 628) / 100.f;
        p.rotSpeed = -1.5f + (std::rand() % 300) / 100.f;
        p.size = 4.f + (std::rand() % 60) / 10.f;
        p.sway = 8.f + (std::rand() % 20);
        p.swayPhase = (std::rand() % 628) / 100.f;
        p.alpha = 180.f + (std::rand() % 60);
    }

    inline void DrawPetal(ImDrawList* dl, ImVec2 c, float s, float rot, ImU32 col)
    {
        float cs = std::cosf(rot), sn = std::sinf(rot);
        auto rotate = [&](float x, float y) {
            return ImVec2(c.x + x * cs - y * sn, c.y + x * sn + y * cs);
            };
        ImVec2 p0 = rotate(0, -s);
        ImVec2 p1 = rotate(s * 0.6f, 0);
        ImVec2 p2 = rotate(0, s);
        ImVec2 p3 = rotate(-s * 0.6f, 0);
        dl->AddQuadFilled(p0, p1, p2, p3, col);
    }
}

inline void Petals()
{
    using namespace ImGuiPetals;

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
        List().clear();
        List().reserve(PETAL_COUNT);
        for (int i = 0; i < PETAL_COUNT; ++i)
        {
            Petal p{}; Spawn(p, w, h, true); List().push_back(p);
        }
    }

    float dt = ImGui::GetIO().DeltaTime;
    if (dt <= 0.f) dt = 1.f / 60.f;
    if (dt > 0.05f) dt = 0.05f;

    ImDrawList* dl = ImGui::GetBackgroundDrawList();
    float t = (float)ImGui::GetTime();

    for (auto& p : List())
    {
        float sway = std::sinf(t * 1.5f + p.swayPhase) * p.sway;
        p.pos.x += (p.vx + sway) * dt;
        p.pos.y += p.vy * dt;
        p.rot += p.rotSpeed * dt;

        if (p.pos.y > h + 20.f || p.pos.x < -30.f || p.pos.x > w + 30.f)
            Spawn(p, w, h, false);

        ImU32 col = IM_COL32(255, 182, 193, (int)p.alpha);
        DrawPetal(dl, p.pos, p.size, p.rot, col);
    }
}
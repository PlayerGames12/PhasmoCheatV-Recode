#pragma once
#include <vector>
#include <cmath>
#include "../Includes.h"

// idk author, sorry

namespace ImGuiStars
{
    struct Star { ImVec2 pos; float twinkle; float speed; float size; };
    struct Meteor { ImVec2 pos; ImVec2 vel; float life; float maxLife; bool active; };

    inline std::vector<Star>& StarsList() { static std::vector<Star> s; return s; }
    inline std::vector<Meteor>& MeteorList() { static std::vector<Meteor> s; return s; }
    inline bool& Initialized() { static bool v = false; return v; }
    inline ImVec2& LastSize() { static ImVec2 v(-1, -1); return v; }
    inline float& MeteorTimer() { static float t = 0.f; return t; }
}

inline void StarrySky()
{
    using namespace ImGuiStars;
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
        StarsList().clear();
        const int N = 180;
        for (int i = 0; i < N; ++i)
        {
            Star s{};
            s.pos = ImVec2((float)(std::rand() % (int)w), (float)(std::rand() % (int)h));
            s.twinkle = (std::rand() % 628) / 100.f;
            s.speed = 0.5f + (std::rand() % 300) / 100.f;
            s.size = 0.5f + (std::rand() % 150) / 100.f;
            StarsList().push_back(s);
        }
        MeteorList().clear();
        MeteorList().resize(5);
    }

    float dt = ImGui::GetIO().DeltaTime;
    if (dt <= 0.f) dt = 1.f / 60.f;
    if (dt > 0.05f) dt = 0.05f;

    ImDrawList* dl = ImGui::GetBackgroundDrawList();
    float t = (float)ImGui::GetTime();

    for (auto& s : StarsList())
    {
        float a = 0.4f + 0.6f * (0.5f + 0.5f * std::sinf(t * s.speed + s.twinkle));
        ImU32 col = IM_COL32(255, 255, 255, (int)(a * 220));
        dl->AddCircleFilled(s.pos, s.size, col, 6);
    }

    MeteorTimer() -= dt;
    if (MeteorTimer() <= 0.f)
    {
        MeteorTimer() = 1.5f + (std::rand() % 400) / 100.f;
        for (auto& m : MeteorList())
        {
            if (!m.active)
            {
                m.active = true;
                m.pos = ImVec2((float)(std::rand() % (int)w), -10.f);
                float sp = 400.f + (std::rand() % 300);
                m.vel = ImVec2(-sp * 0.7f, sp);
                m.maxLife = 0.6f + (std::rand() % 40) / 100.f;
                m.life = m.maxLife;
                break;
            }
        }
    }

    for (auto& m : MeteorList())
    {
        if (!m.active) continue;
        m.pos.x += m.vel.x * dt;
        m.pos.y += m.vel.y * dt;
        m.life -= dt;
        if (m.life <= 0.f || m.pos.y > h + 50.f || m.pos.x < -50.f)
        {
            m.active = false; continue;
        }
        float k = m.life / m.maxLife;
        ImVec2 tail(m.pos.x - m.vel.x * 0.08f, m.pos.y - m.vel.y * 0.08f);
        ImU32 head = IM_COL32(255, 255, 255, (int)(255 * k));
        ImU32 end = IM_COL32(255, 255, 255, 0);
        dl->AddLine(tail, m.pos, head, 2.0f);
        dl->AddLine(tail, m.pos, end, 0.5f);
        dl->AddCircleFilled(m.pos, 2.5f, head, 8);
    }
}
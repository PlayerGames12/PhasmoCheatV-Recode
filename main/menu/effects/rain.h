#pragma once

// I don't known author, but I know this code is open source and free to use, so here it is.

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "../Includes.h"

#ifndef RAIN_DROP_COUNT
#define RAIN_DROP_COUNT 150
#endif

#ifndef RAIN_SPEED_MUL
#define RAIN_SPEED_MUL 1.0f
#endif


//Rain()
//    draws animated rain filling the current window.
//    call before your widgets so rain sits behind them.

//Rain_Reset()
//    resets all drop positions next frame.
//    useful when you resize or recreate the window.

namespace ImGuiRain
{
    struct Drop
    {
        ImVec2 pos;
        float  speed;
        float  length;
        float  angle;
        float  alpha;
    };

    inline std::vector<Drop>& Drops()
    {
        static std::vector<Drop> s;
        return s;
    }

    inline bool& Initialized() { static bool   v = false;       return v; }
    inline bool& NeedsReset() { static bool   v = false;       return v; }
    inline ImVec2& LastSize() { static ImVec2 v(-1.f, -1.f);   return v; }

    inline void SpawnDrop(Drop& d, float w, float h, bool random_y = false)
    {
        d.pos.x = (float)(std::rand() % (int)w);
        d.pos.y = random_y
            ? (float)(std::rand() % (int)h)   // scatter on init
            : -32.f;                           // spawn above window
        d.speed = 300.f + (float)(std::rand() % 200);
        d.length = 8.f + (float)(std::rand() % 16);
        d.angle = 0.08f + (float)(std::rand() % 10) / 100.f;
        d.alpha = 80.f + (float)(std::rand() % 120);
    }
} // namespace ImGuiRain

inline void Rain_Reset()
{
    ImGuiRain::NeedsReset() = true;
}

inline void Rain()
{
    using namespace ImGuiRain;

    // bail if window isn't ready
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (!window || window->SkipItems) return;

    ImVec2 screen = ImGui::GetIO().DisplaySize;
    const ImVec2 wmin = ImVec2(0, 0);
    const ImVec2 wmax = screen;
    const float w = screen.x;
    const float h = screen.y;
    if (w <= 5.f || h <= 5.f) return;

    // seed once
    if (!Initialized())
    {
        std::srand((unsigned)std::time(nullptr));
        Initialized() = true;
    }

    // repopulate drops if the window size changed or a reset was requested
    bool size_changed =
        LastSize().x < 0.f ||
        std::fabs(LastSize().x - w) > 1.f ||
        std::fabs(LastSize().y - h) > 1.f;

    if (size_changed || NeedsReset())
    {
        LastSize() = ImVec2(w, h);
        NeedsReset() = false;

        Drops().clear();
        Drops().reserve(RAIN_DROP_COUNT);

        for (int i = 0; i < RAIN_DROP_COUNT; ++i)
        {
            Drop d{};
            SpawnDrop(d, w, h, /*random_y=*/true);
            Drops().push_back(d);
        }
    }

    // clamp delta time so a stall doesn't teleport drops
    float dt = ImGui::GetIO().DeltaTime;
    if (dt <= 0.f)        dt = 1.f / 60.f;
    if (dt > 1.f / 20.f)  dt = 1.f / 20.f;

    // update and draw
    ImDrawList* dl = ImGui::GetBackgroundDrawList();

    const float speed_mul = RAIN_SPEED_MUL;

    for (auto& d : Drops())
    {
        // move
        d.pos.y += d.speed * dt * speed_mul;
        d.pos.x += d.speed * std::tanf(d.angle) * dt * speed_mul;

        // wrap around edges
        if (d.pos.y > h + d.length)
            SpawnDrop(d, w, h, /*random_y=*/false);
        if (d.pos.x > w + 10.f) d.pos.x = -10.f;
        if (d.pos.x < -10.f)     d.pos.x = w + 10.f;

        // screen positions
        const ImVec2 head(wmin.x + d.pos.x, wmin.y + d.pos.y);
        const ImVec2 tail(head.x - d.length * std::sinf(d.angle),
            head.y - d.length * std::cosf(d.angle));

        // head bright, tail fades out
        const ImU32 col_head = IM_COL32(180, 210, 255, (int)d.alpha);
        const ImU32 col_tail = IM_COL32(180, 210, 255, 0);

        dl->AddLine(tail, head, col_head, 1.5f);
        dl->AddLine(tail, head, col_tail, 0.5f);
    }
}

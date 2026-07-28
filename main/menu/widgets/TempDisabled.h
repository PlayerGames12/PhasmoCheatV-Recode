#pragma once

#include "imgui.h"
#include <type_traits>

namespace wImGui
{
    namespace detail
    {
        struct TempDisableState
        {
            int remaining = 0;
        };

        inline TempDisableState& State()
        {
            static TempDisableState s;
            return s;
        }

        inline void DrawBadge(const char* text)
        {
            const ImVec2 pad(6.0f, 2.0f);

            const ImVec2 textSize = ImGui::CalcTextSize(text);
            const ImVec2 pos = ImGui::GetCursorScreenPos();
            const ImVec2 size(textSize.x + pad.x * 2.0f,
                textSize.y + pad.y * 2.0f);

            ImDrawList* draw = ImGui::GetWindowDrawList();

            const ImU32 bg = ImGui::GetColorU32(ImVec4(0.90f, 0.55f, 0.15f, 0.20f));
            const ImU32 border = ImGui::GetColorU32(ImVec4(0.90f, 0.55f, 0.15f, 0.55f));
            const ImU32 textColor = ImGui::GetColorU32(ImVec4(0.95f, 0.72f, 0.35f, 1.00f));

            draw->AddRectFilled(
                pos,
                ImVec2(pos.x + size.x, pos.y + size.y),
                bg,
                4.0f);

            draw->AddRect(
                pos,
                ImVec2(pos.x + size.x, pos.y + size.y),
                border,
                4.0f);

            draw->AddText(
                ImVec2(pos.x + pad.x, pos.y + pad.y),
                textColor,
                text);

            ImGui::Dummy(size);
        }

        inline void DrawBadgeAfterItem()
        {
            ImGui::SameLine();
            DrawBadge("Temp disabled");
        }
    }

    inline void TempDisabled(int count)
    {
        detail::State().remaining = count;
    }

    template<typename Fn>
    auto Wrap(Fn&& fn) -> decltype(fn())
    {
        auto& state = detail::State();

        if (state.remaining <= 0)
            return fn();

        state.remaining--;

        if constexpr (std::is_void_v<decltype(fn())>)
        {
            ImGui::BeginDisabled();
            fn();
            ImGui::EndDisabled();

            detail::DrawBadgeAfterItem();
        }
        else
        {
            ImGui::BeginDisabled();

            auto result = fn();

            ImGui::EndDisabled();

            detail::DrawBadgeAfterItem();

            return result;
        }
    }
}

#define WD(expr) wImGui::Wrap([&]() { return expr; })
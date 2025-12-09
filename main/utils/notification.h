#pragma once
#include "../Includes.h"
namespace PhasmoCheatV::Notifications
{
    enum class NotificationType : uint8_t
    {
        Info,
        Warning,
        Error,
        Success
    };
    struct Notification
    {
        std::string Message;
        NotificationType Type;
        float LifeTime;
        float Progress = 0.0f;
        bool Closed = false;
    };
    inline std::vector<Notification> notifications;
#define NOTIFY_INFO(message, lifeTime) \
        PhasmoCheatV::Notifications::AddNotification(message, PhasmoCheatV::Notifications::NotificationType::Info, lifeTime)
#define NOTIFY_WARNING(message, lifeTime) \
        PhasmoCheatV::Notifications::AddNotification(message, PhasmoCheatV::Notifications::NotificationType::Warning, lifeTime)
#define NOTIFY_ERROR(message, lifeTime) \
        PhasmoCheatV::Notifications::AddNotification(message, PhasmoCheatV::Notifications::NotificationType::Error, lifeTime)
#define NOTIFY_SUCCESS(message, lifeTime) \
        PhasmoCheatV::Notifications::AddNotification(message, PhasmoCheatV::Notifications::NotificationType::Success, lifeTime)
#define NOTIFY_INFO_QUICK(message) NOTIFY_INFO(message, 4.0f)
#define NOTIFY_WARNING_QUICK(message) NOTIFY_WARNING(message, 5.0f)
#define NOTIFY_ERROR_QUICK(message) NOTIFY_ERROR(message, 6.0f)
#define NOTIFY_SUCCESS_QUICK(message) NOTIFY_SUCCESS(message, 4.0f)
    struct Config
    {
        static constexpr float DefaultLife = 5.0f;
        static constexpr float AnimationSpeed = 6.0f;
        static constexpr float Width = 380.0f;
        static constexpr float Padding = 16.0f;
        static constexpr float WindowRounding = 6.0f;
        static constexpr float BorderSize = 2.0f;
        static constexpr ImVec2 WindowPadding = ImVec2(12.0f, 8.0f);
        static constexpr float CloseSize = 18.0f;
        static constexpr float ProgressHeight = 4.0f;
    };
    struct NotificationStyle
    {
        ImVec4 Bg;
        ImVec4 Header;
        ImVec4 Text;
        const char* HeaderText;
    };
    inline NotificationStyle GetStyle(NotificationType type, float alpha)
    {
        switch (type)
        {
        case NotificationType::Info:    return { ImVec4(0.1f,0.1f,0.35f,alpha), ImVec4(0.2f,0.2f,0.6f,alpha), ImVec4(0.9f,0.9f,1.0f,alpha), "INFO" };
        case NotificationType::Warning: return { ImVec4(0.35f,0.25f,0.1f,alpha), ImVec4(0.55f,0.4f,0.1f,alpha), ImVec4(1.0f,0.9f,0.7f,alpha), "WARNING" };
        case NotificationType::Error:   return { ImVec4(0.35f,0.1f,0.1f,alpha), ImVec4(0.55f,0.15f,0.15f,alpha), ImVec4(1.0f,0.7f,0.7f,alpha), "ERROR" };
        case NotificationType::Success: return { ImVec4(0.1f,0.35f,0.1f,alpha), ImVec4(0.15f,0.55f,0.15f,alpha), ImVec4(0.7f,1.0f,0.7f,alpha), "SUCCESS" };
        default: return { ImVec4(0.1f,0.1f,0.35f,alpha), ImVec4(0.2f,0.2f,0.6f,alpha), ImVec4(0.9f,0.9f,1.0f,alpha), "INFO" };
        }
    }
    inline void AddNotification(const std::string& msg, NotificationType type, float lifeTime = Config::DefaultLife)
    {
        notifications.push_back({ msg, type, lifeTime });
    }
    inline void UpdateNotifications()
    {
        const float dt = ImGui::GetIO().DeltaTime;
        for (auto& n : notifications)
        {
            n.Progress = std::clamp(n.Progress + dt * Config::AnimationSpeed, 0.0f, 1.0f);
            n.LifeTime -= dt;
        }
        std::erase_if(notifications, [](auto& n) { return n.LifeTime <= 0.0f || n.Closed; });
    }
    inline float GetHeight(const Notification& n)
    {
        if (n.Progress <= 0.0f) return 0.0f;
        const float textWidth = Config::Width - Config::WindowPadding.x * 2;
        ImVec2 ts = ImGui::CalcTextSize(n.Message.c_str(), nullptr, false, textWidth);
        return ImGui::GetTextLineHeightWithSpacing() + ts.y + Config::ProgressHeight + Config::WindowPadding.y * 3;
    }
    inline void DrawNotification(const Notification& n, float posY)
    {
        float alpha = n.Progress;
        if (alpha <= 0.0f) return;
        NotificationStyle style = GetStyle(n.Type, alpha);
        const ImVec2 screen = ImGui::GetIO().DisplaySize;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, Config::WindowRounding);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, Config::BorderSize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, Config::WindowPadding);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, style.Bg);
        ImGui::PushStyleColor(ImGuiCol_Text, style.Text);
        ImGui::PushStyleColor(ImGuiCol_Button, style.Header);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(style.Header.x * 1.2f, style.Header.y * 1.2f, style.Header.z * 1.2f, alpha));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(style.Header.x * 0.8f, style.Header.y * 0.8f, style.Header.z * 0.8f, alpha));
        constexpr ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoFocusOnAppearing;
        ImGui::SetNextWindowSize(ImVec2(Config::Width, 0), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(screen.x - Config::Padding - Config::Width, posY), ImGuiCond_Always, ImVec2(0.0f, 1.0f));
        ImGui::Begin(std::format("Notification##{}", (void*)&n).c_str(), nullptr, flags);
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
        ImGui::Text("%s", style.HeaderText);
        ImGui::SameLine(ImGui::GetContentRegionAvail().x - Config::CloseSize);
        ImVec2 crossPos = ImGui::GetCursorScreenPos();
        ImGui::SetCursorScreenPos(crossPos);
        ImGui::InvisibleButton("CloseInvisible", ImVec2(Config::CloseSize + 6.0f, Config::CloseSize + 6.0f));
        if (ImGui::IsItemClicked())
            const_cast<Notification&>(n).Closed = true;
        ImGui::SetCursorScreenPos(crossPos);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, alpha));
        ImGui::Text("X");
        ImGui::PopStyleColor();
        ImGui::PopFont();
        ImGui::Separator();
        ImGui::PushTextWrapPos(Config::Width - Config::WindowPadding.x * 2);
        ImGui::TextUnformatted(n.Message.c_str());
        ImGui::PopTextWrapPos();
        float prog = std::max<float>(0.0f, n.LifeTime / Config::DefaultLife);
        ImGui::PushStyleColor(ImGuiCol_PlotHistogram, style.Header);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, alpha * 0.5f));
        ImGui::ProgressBar(prog, ImVec2(-1, Config::ProgressHeight), "");
        ImGui::PopStyleColor(2);
        ImGui::End();
        ImGui::PopStyleColor(5);
        ImGui::PopStyleVar(3);
    }
    inline void RenderNotifications()
    {
        UpdateNotifications();
        if (notifications.empty()) return;
        const ImVec2 screen = ImGui::GetIO().DisplaySize;
        float curY = screen.y - Config::Padding;
        std::vector<float> heights;
        heights.reserve(notifications.size());
        for (auto it = notifications.rbegin(); it != notifications.rend(); ++it)
            heights.push_back(GetHeight(*it));
        size_t idx = 0;
        for (auto it = notifications.rbegin(); it != notifications.rend(); ++it, ++idx)
        {
            float h = heights[idx];
            if (h > 0.0f)
            {
                DrawNotification(*it, curY);
                curY -= h + Config::Padding;
            }
        }
    }
    inline void ClearAll() { notifications.clear(); }
    inline size_t Count() { return notifications.size(); }
    inline bool HasActive() { return !notifications.empty(); }
}
#include "menu.h"
#include "styles.h"

using namespace PhasmoCheatV;

SDK::CursorLockMode Menu::previousCursorLockMode = SDK::CursorLockMode::None;

void Menu::Initialize()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    SetMenuStyle();
    Initialized = true;
}

void Menu::Render()
{
    constexpr ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse;

    constexpr int menuWidth = 850;
    constexpr int menuHeight = 600;
    constexpr float tabBarWidth = 180.f;

    ImGui::SetNextWindowSize(ImVec2(menuWidth * dpiScale, menuHeight * dpiScale), ImGuiCond_Once);
    ImGui::SetNextWindowBgAlpha(1.0f);

    ImGui::Begin("Protected by VAAC##MainMenu", nullptr, windowFlags);

    ImVec2 contentSize = ImGui::GetContentRegionAvail();
    ImGui::BeginChild("MainLayout", contentSize, false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImGui::BeginChild("TabBar", ImVec2(tabBarWidth * dpiScale, contentSize.y), true);
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 2));
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]); // Закоментированы шрифты

        ImGui::SetCursorPosX((tabBarWidth * dpiScale - ImGui::CalcTextSize("PHASMOCHEATV").x) * 0.5f);
        ImGui::TextColored(accentPurple, "PHASMOCHEATV");
        ImGui::SetCursorPosX((tabBarWidth * dpiScale - ImGui::CalcTextSize("VCom Team").x) * 0.5f);
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.8f, 1.0f), "VCom Team");
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::PopFont(); 

        auto DrawTabButton = [&](const char* label, int tabIndex) {
            ImGui::PushStyleColor(ImGuiCol_Button, menu.currentTab == tabIndex ? accentPurpleDark : darkerBg);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, accentPurple);
            if (ImGui::Button(label, ImVec2(tabBarWidth * dpiScale - 15, 45 * dpiScale))) {
                menu.currentTab = tabIndex;
            }
            ImGui::PopStyleColor(2);
            };

        DrawTabButton("FEATURES", 0);
        DrawTabButton("SETTINGS", 1);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::SetCursorPosY(contentSize.y - 50 * dpiScale);
        ImGui::SetCursorPosX((tabBarWidth * dpiScale - (tabBarWidth * dpiScale - 15)) / 2);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.05f, 0.10f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.45f, 0.05f, 0.15f, 1.00f));
        if (ImGui::Button("UNLOAD CHEAT", ImVec2(tabBarWidth * dpiScale - 15, 40 * dpiScale))) {
            menu.Toggle();
            CheatWork = false;
        }
        ImGui::PopStyleColor(2);

        ImGui::PopStyleVar();
    }
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("ContentArea", ImVec2(contentSize.x - tabBarWidth * dpiScale, contentSize.y), true);
    {
        switch (menu.currentTab)
        {
        case 0:
            ImGui::BeginChild("FeaturesContent", ImVec2(0, 0), true);
            {
                if (GET_FEATURE_HANDLER())
                {
                    GET_FEATURE_HANDLER()->RenderMenu();
                }
                else
                {
                    LOG_ERROR("GET_FEATURE_HANDLER not initialized!");
                }
            }
            ImGui::EndChild();
            break;

        case 1:
            ImGui::Spacing();
            ImGui::SetCursorPosX(20 * dpiScale);
            ImGui::BeginGroup();
            ImGui::TextColored(accentPurple, "SETTINGS");
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0, 10));

            ImGui::Text("Menu Toggle Key:");
            static char keyName[64] = "";
            if (ImGui::Button("Click to set new key", ImVec2(tabBarWidth * dpiScale - 15, 30 * dpiScale)))
            {
                static bool waitingForInput = false;
                waitingForInput = !waitingForInput;

                if (waitingForInput)
                {
                    ImGui::OpenPopup("Set Menu Key");
                }
            }

            ImGui::SameLine();
            ImGui::Text(Utils::getKeyName(MenuToggleKey).c_str());

            if (ImGui::BeginPopupModal("Set Menu Key", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Press any key to set as menu toggle...");
                ImGui::Separator();

                if (ImGui::Button("Cancel", ImVec2(120, 0)))
                {
                    ImGui::CloseCurrentPopup();
                }

                for (int key = 0; key < 256; key++)
                {
                    if (GetAsyncKeyState(key) & 0x8000)
                    {
                        MenuToggleKey = key;
                        ImGui::CloseCurrentPopup();
                        break;
                    }
                }

                ImGui::EndPopup();
            }

            ImGui::Dummy(ImVec2(0, 10));

            ImGui::TextColored(accentPurple, "CREDITS");
            ImGui::Separator();
            ImGui::TextColored(ImVec4(0.8f, 0.6f, 1.0f, 1.0f), "VCom Team");
            ImGui::BulletText("ViniLog - Lead (writing recode solo)");
            ImGui::BulletText("Nastya - Designer");
            ImGui::BulletText("Artur - Lead Coder");
            ImGui::BulletText("Anna - Designer");
            ImGui::BulletText("Kirill - Assistant Lead Coder");
            ImGui::BulletText("Maxim - Coder");
            ImGui::BulletText("Nikita - Coder");
            ImGui::BulletText("Vanya - Coder");
            ImGui::BulletText("Ilya - Tester");

            ImGui::Dummy(ImVec2(0, 10));
            ImGui::TextColored(ImVec4(0.6f, 0.8f, 1.0f, 1.0f), "Special Thanks");
            ImGui::BulletText("@DashaAngelBars, @TraKKRR_lIo, @MT_FORGET, @nypdgov, Evelien");

            ImGui::Dummy(ImVec2(0, 10));
            ImGui::TextColored(ImVec4(0.6f, 0.8f, 1.0f, 1.0f), "By ViniLog");
            ImGui::BulletText("Olesya i love you");

            ImGui::EndGroup();
            break;
        }
    }
    ImGui::EndChild();
    ImGui::EndChild();
    ImGui::End();
}

void Menu::Toggle()
{
    menu.Open = !menu.Open;

    if (menu.Open)
    {
        previousCursorLockMode = SDK::Cursor_Get_LockState(nullptr);
        SDK::Cursor_Set_Visible(true, nullptr);
        SDK::Cursor_Set_LockState(SDK::CursorLockMode::None, nullptr);
    }
    else
    {
        if (previousCursorLockMode != SDK::CursorLockMode::None)
            SDK::Cursor_Set_Visible(false, nullptr);

        SDK::Cursor_Set_LockState(previousCursorLockMode, nullptr);
    }
}
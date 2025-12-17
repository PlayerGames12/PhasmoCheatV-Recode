#include "menu.h"
#include "styles.h"
#include <random>
#include <chrono>
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

// TODO: FIX CRASH FULLBRIGHT.

SDK::CursorLockMode Menu::previousCursorLockMode = SDK::CursorLockMode::None;

void Menu::Initialize() {
    ImGui::CreateContext();
    SetMenuDefaultStyle();
    InitFonts();
    Initialized = true;
}

void Menu::NewYear()
{
    static std::vector<ImVec2> snow(80);
    static bool init = false;
    if (!init) {
        init = true;
        for (auto& s : snow)
            s = ImVec2((float)(rand() % (int)ImGui::GetIO().DisplaySize.x),
                (float)(rand() % (int)ImGui::GetIO().DisplaySize.y));
    }

    auto& io = ImGui::GetIO();
    ImDrawList* dl = ImGui::GetBackgroundDrawList();

    ImGui::PushFont(io.Fonts->Fonts[6]);
    ImU32 snowColor = IM_COL32(230, 230, 255, 200);
    for (auto& s : snow) {
        dl->AddText(s, snowColor, "S");
        s.y += 0.4f + (rand() % 100) / 200.f;
        if (s.y > io.DisplaySize.y)
            s = ImVec2((float)(rand() % (int)io.DisplaySize.x), -10.f);
    }
    ImGui::PopFont();
}


void Menu::Render()
{
    constexpr ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse;

    constexpr int menuWidth = 900;
    constexpr int menuHeight = 650;
    constexpr float tabBarWidth = 200.f;

    ImGui::SetNextWindowSize(ImVec2(menuWidth * dpiScale, menuHeight * dpiScale), ImGuiCond_Once);
    ImGui::SetNextWindowBgAlpha(1.0f);

    NewYear();

    ImGui::Begin("##MainMenu", nullptr, windowFlags);

    ImVec2 contentSize = ImGui::GetContentRegionAvail();
    ImGui::BeginChild("MainLayout", contentSize, false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImGui::BeginChild("TabBar", ImVec2(tabBarWidth * dpiScale, contentSize.y), true);
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 4));

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
        ImGui::SetCursorPosY(20 * dpiScale);

        ImGui::SetCursorPosX((tabBarWidth * dpiScale - ImGui::CalcTextSize("PHASMOCHEATV").x) * 0.5f);
        ImGui::TextColored(accentPurple, "PHASMOCHEATV");

        ImGui::SetCursorPosX((tabBarWidth * dpiScale - ImGui::CalcTextSize("by VCom Team").x) * 0.5f);
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.8f, 0.8f), "by VCom Team");
        ImGui::PopFont();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10 * dpiScale);
        ImGui::Separator();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20 * dpiScale);

        auto DrawTabButton = [&](const char* label, int tabIndex) {
            bool isActive = menu.currentTab == tabIndex;
            ImVec2 sz(tabBarWidth * dpiScale - 40, 50 * dpiScale);
            float x = (tabBarWidth * dpiScale - sz.x) * 0.5f;
            ImGui::SetCursorPosX(x);

            ImGui::PushStyleColor(ImGuiCol_Button, isActive ? accentPurpleDark : ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, isActive ? accentPurple : ImVec4(0.15f, 0.15f, 0.15f, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, accentPurpleLight);
            ImGui::PushStyleColor(ImGuiCol_Text, isActive ? ImVec4(1, 1, 1, 1) : ImVec4(0.8f, 0.8f, 0.9f, 1));

            if (ImGui::Button(label, sz)) menu.currentTab = tabIndex;

            if (isActive) {
                auto p0 = ImGui::GetItemRectMin();
                auto p1 = ImGui::GetItemRectMax();
                ImGui::GetWindowDrawList()->AddRectFilled(
                    ImVec2(p0.x, p1.y - 2), p1, ImGui::GetColorU32(accentPurpleLight)
                );
            }

            ImGui::PopStyleColor(4);
            };

        DrawTabButton("FEATURES", 0);
        DrawTabButton("SETTINGS", 1);
        if (IsDebugging)
            DrawTabButton("TEST", 2);

        float bottomBlock = 120 * dpiScale;

        ImGui::SetCursorPosY(contentSize.y - bottomBlock);

        ImGui::Separator();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20 * dpiScale);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 0.3f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.2f, 0.2f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.6f, 0.6f, 1.0f));

        ImVec2 sz(tabBarWidth * dpiScale - 40, 45 * dpiScale);
        float x = (tabBarWidth * dpiScale - sz.x) * 0.5f;
        ImGui::SetCursorPosX(x);

        if (ImGui::Button("UNLOAD CHEAT", sz)) {
            menu.Toggle();
            CheatWork = false;
        }

        ImGui::PopStyleColor(4);

        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30 * dpiScale);
        ImGui::Separator();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5 * dpiScale);
        ImGui::SetCursorPosX((tabBarWidth * dpiScale - ImGui::CalcTextSize("v2.1 | MIT License").x) * 0.5f);
        ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.6f, 0.7f), "v2.1 | MIT License");

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
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10 * dpiScale);

                if (GET_FEATURE_HANDLER())
                {
                    GET_FEATURE_HANDLER()->RenderMenu();
                }
                else
                {
                    ImGui::SetCursorPos(ImVec2(
                        (ImGui::GetWindowWidth() - ImGui::CalcTextSize("Features not available").x) * 0.5f,
                        (ImGui::GetWindowHeight() - ImGui::GetTextLineHeight()) * 0.5f
                    ));
                    ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "Features not available");
                }
            }
            ImGui::EndChild();
            break;

        case 1:
            ImGui::SetCursorPosY(20 * dpiScale);
            ImGui::SetCursorPosX(25 * dpiScale);
            ImGui::BeginGroup();

            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
            ImGui::TextColored(accentPurple, "SETTINGS");
            ImGui::PopFont();
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0, 15));

            ImGui::BeginChild("GeneralSettings", ImVec2(0, 67 * dpiScale), true);
            {
                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[7]);
                ImGui::TextColored(ImVec4(0.8f, 0.8f, 1.0f, 1.0f), "General Settings");
                ImGui::PopFont();

                ImGui::Dummy(ImVec2(0, 5));
                ImGui::Text("Menu Toggle Key:");
                ImGui::SameLine(150 * dpiScale);

                ImGui::PushStyleColor(ImGuiCol_Button, accentPurpleDark);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, accentPurple);
                if (ImGui::Button("Set New Key", ImVec2(120 * dpiScale, 30 * dpiScale)))
                {
                    static bool waitingForInput = false;
                    waitingForInput = !waitingForInput;
                    if (waitingForInput)
                    {
                        ImGui::OpenPopup("Set Menu Key");
                    }
                }
                ImGui::PopStyleColor(2);

                ImGui::SameLine();
                ImGui::TextColored(accentPurpleLight, Utils::getKeyName(MenuToggleKey).c_str());

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
            }
            ImGui::EndChild();

            ImGui::Dummy(ImVec2(0, 20));

            ImGui::BeginChild("OpenSource", ImVec2(0, 136 * dpiScale), true);
            {
                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[7]);
                ImGui::TextColored(accentPurple, "OPEN SOURCE");
                ImGui::PopFont();
                ImGui::Separator();
                ImGui::Dummy(ImVec2(0, 9));

                ImGui::TextColored(ImVec4(0.6f, 0.8f, 1.0f, 1.0f), "GitHub Repository");
                ImGui::SameLine(200 * dpiScale);

                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.3f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.4f, 1.0f));
                if (ImGui::Button("Open GitHub", ImVec2(120 * dpiScale, 25 * dpiScale)))
                {
                    ShellExecuteA(0, "open", "https://github.com/PlayerGames12/PhasmoCheatV-Recode", 0, 0, SW_SHOW);
                }
                ImGui::PopStyleColor(2);

                ImGui::Dummy(ImVec2(0, 8));
                ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "License: MIT");
                ImGui::TextWrapped("This project is open source and available under MIT License. Feel free to contribute!");
            }
            ImGui::EndChild();

            ImGui::Dummy(ImVec2(0, 20));

            ImGui::BeginChild("Credits", ImVec2(0, 0), true);
            {
                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[7]);
                ImGui::TextColored(accentPurple, " CREDITS");
                ImGui::PopFont();
                ImGui::Separator();
                ImGui::Dummy(ImVec2(0, 10));

                ImGui::TextColored(ImVec4(0.8f, 0.6f, 1.0f, 1.0f), " VCom Team");
                ImGui::Dummy(ImVec2(0, 5));

                ImGui::Columns(2, "TeamColumns", false);
                ImGui::SetColumnWidth(0, 250 * dpiScale);

                ImGui::BulletText("Artur - Coder");
                ImGui::BulletText("Nastya - Designer");
                ImGui::BulletText("Anna - Designer");
                ImGui::BulletText("ViniLog - Lead Coder");

                ImGui::NextColumn();

                ImGui::BulletText("Kirill - Assistant Lead");
                ImGui::BulletText("Maxim - Coder");
                ImGui::BulletText("Nikita - Coder");
                ImGui::BulletText("Vanya - Coder");
                ImGui::BulletText("Ilya - Tester");

                ImGui::Columns(1);

                ImGui::Dummy(ImVec2(0, 5));

                ImGui::TextColored(ImVec4(0.6f, 0.8f, 1.0f, 1.0f), " Special Thanks");
                ImGui::Dummy(ImVec2(0, 5));
                ImGui::TextWrapped("@DashaAngelBars, @TraKKRR_lIo, @MT_FORGET, @nypdgov");
                ImGui::TextWrapped("Evelien for some functions, as well as the design of the function system");
            }
            ImGui::EndChild();

            ImGui::EndGroup();
            break;
        case 2:
            if (IsDebugging)
            {
                ImGui::BeginChild("TestContent", ImVec2(0, 0), true);

                if (ImGui::Button("Test set Ghost"))
                {
                    // Work good, but UI not updated
                    auto* jc = Utils::GetMainMenuJournal();
                    SDK::JournalController_SelectGhost(jc, SDK::GhostType::Demon, nullptr);
                    LOG_INFO("JournalController_SelectGhost is called");
                }

                if (ImGui::Button("Test force exit"))
                {
                    // Crash the game. Need call in the main thread of the game. 
                    // Not work in online. 
                    // Need real data player in PhotonMessageInfo. 
                    // Use GetLocalPlayer, gettimestamp and more most likely

                    auto* messageInfo = Utils::CreatePhotonMessageInfo();

                    SDK::ExitLevel* exitLevel2 = Utils::GetExitLevel();

                    if (messageInfo)
                        LOG_INFO("Photon create and = ", messageInfo);
                    else
                        LOG_INFO("Photon created failed.");

                    if (exitLevel2)
                        SDK::ExitLevel_Exit(exitLevel2, messageInfo, nullptr);
                }
                
                if (ImGui::Button("Call test"))
                {
					ForTestsFlag = true;
                }
                ImGui::EndChild();
            }
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
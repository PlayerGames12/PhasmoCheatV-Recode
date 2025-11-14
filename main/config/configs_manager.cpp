#include "configs_manager.h"
#include "configs.h"
#include "config.h"

using namespace PhasmoCheatV::Features::Configs;

ConfigsManager::ConfigsManager() : FeatureCore("ConfigsManager", TYPE_CONFIGS)
{
    std::memset(newConfigName, 0, sizeof(newConfigName));
    std::memset(importData, 0, sizeof(importData));
    showCreate = showImport = showDelete = showExport = false;
    
    ConfigsM::InitializeConfigs();
}

void ConfigsManager::OnMenuRender()
{
    ImGui::BeginChild("ConfigsContent", ImVec2(0, 0), true);
    
    if (ImGui::Button("Create New", ImVec2(120, 30)))
    {
        showCreate = true;
        std::memset(newConfigName, 0, sizeof(newConfigName));
    }
    
    ImGui::SameLine();
    
    if (ImGui::Button("Import", ImVec2(120, 30)))
    {
        showImport = true;
        std::memset(importData, 0, sizeof(importData));
    }
    
    ImGui::SameLine();
    
    if (ImGui::Button("Save Current", ImVec2(120, 30)))
    {
        Config::SaveConfig();
    }
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    auto configs = ConfigsM::GetConfigs();
    
    if (configs.empty())
    {
        ImGui::Text("No configs found");
    }
    else
    {
        if (ImGui::BeginTable("Configs", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 150);
            ImGui::TableSetupColumn("Modified", ImGuiTableColumnFlags_WidthFixed, 120);
            ImGui::TableSetupColumn("Actions", ImGuiTableColumnFlags_WidthFixed, 200);
            ImGui::TableHeadersRow();
            
            for (const auto& config : configs)
            {
                ImGui::TableNextRow();
                
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", config.name.c_str());
                
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", config.modifiedDate.c_str());
                
                ImGui::TableSetColumnIndex(2);
                
                if (ImGui::Button(("Load##" + config.name).c_str(), ImVec2(50, 0)))
                {
                    ConfigsM::LoadConfig(config.name);
                }
                
                ImGui::SameLine();
                
                if (ImGui::Button(("Export##" + config.name).c_str(), ImVec2(50, 0)))
                {
                    configToExport = config.name;
                    showExport = true;
                }
                
                ImGui::SameLine();
                
                if (ImGui::Button(("Delete##" + config.name).c_str(), ImVec2(50, 0)))
                {
                    selectedConfig = config.name;
                    showDelete = true;
                }
            }
            
            ImGui::EndTable();
        }
    }
    
    if (showCreate) ImGui::OpenPopup("Create Config");
    if (showImport) ImGui::OpenPopup("Import Config");
    if (showDelete) ImGui::OpenPopup("Delete Config");
    if (showExport) ImGui::OpenPopup("Export Config");
    
    if (ImGui::BeginPopupModal("Create Config", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Config name:");
        ImGui::InputText("##Name", newConfigName, sizeof(newConfigName));
        
        if (ImGui::Button("Create"))
        {
            if (strlen(newConfigName) > 0 && !ConfigsM::ConfigExists(newConfigName))
            {
                if (ConfigsM::SaveConfig(newConfigName))
                {
                    showCreate = false;
                    ImGui::CloseCurrentPopup();
                }
            }
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("Cancel"))
        {
            showCreate = false;
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::EndPopup();
    }
    
    if (ImGui::BeginPopupModal("Import Config", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Paste Base64 data:");
        ImGui::InputTextMultiline("##Import", importData, sizeof(importData), ImVec2(300, 100));
        
        if (ImGui::Button("Import"))
        {
            if (strlen(importData) > 0)
            {
                if (ConfigsM::ImportConfig(importData))
                {
                    showImport = false;
                    ImGui::CloseCurrentPopup();
                }
            }
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("Cancel"))
        {
            showImport = false;
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("Delete Config", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Delete %s?", selectedConfig.c_str());
        
        if (ImGui::Button("Yes"))
        {
            ConfigsM::DeleteConfig(selectedConfig);
            showDelete = false;
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("No"))
        {
            showDelete = false;
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::EndPopup();
    }
    
    if (ImGui::BeginPopupModal("Export Config", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Config '%s' exported to clipboard!", configToExport.c_str());
        ImGui::Text("Share this key with others:");
        
        std::string exportedKey = ConfigsM::ExportConfig(configToExport);
        
        if (!exportedKey.empty())
        {
            if (exportedKey.length() > 50)
            {
                std::string shortKey = exportedKey.substr(0, 50) + "...";
                ImGui::Text("%s", shortKey.c_str());
                ImGui::Text("Full key copied to clipboard!");
            }
            else
            {
                ImGui::Text("%s", exportedKey.c_str());
            }
            
            if (OpenClipboard(nullptr))
            {
                EmptyClipboard();
                HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, exportedKey.size() + 1);
                if (hg)
                {
                    memcpy(GlobalLock(hg), exportedKey.c_str(), exportedKey.size() + 1);
                    GlobalUnlock(hg);
                    SetClipboardData(CF_TEXT, hg);
                }
                CloseClipboard();
            }
        }
        else
        {
            ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "Failed to export config!");
        }
        
        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            showExport = false;
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::EndPopup();
    }
    
    ImGui::EndChild();
}
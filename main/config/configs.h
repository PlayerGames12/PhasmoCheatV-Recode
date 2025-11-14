#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::ConfigsM
{
    struct ConfigInfo
    {
        std::string name;
        std::string filename;
        std::string modifiedDate;
        size_t size;
    };

    void InitializeConfigs();
    void RefreshConfigs();
    std::vector<ConfigInfo> GetConfigs();
    bool LoadConfig(const std::string& name);
    bool SaveConfig(const std::string& name);
    bool DeleteConfig(const std::string& name);
    std::string ExportConfig(const std::string& name);
    bool ImportConfig(const std::string& data);
    bool ConfigExists(const std::string& name);
}
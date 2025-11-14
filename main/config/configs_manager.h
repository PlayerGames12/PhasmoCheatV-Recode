#pragma once
#include "../features/feature.h"

namespace PhasmoCheatV::Features::Configs
{
    class ConfigsManager : public FeatureCore
    {
    public:
        ConfigsManager();
        void OnActivate() override {}
        void OnDeactivate() override {}
        void OnRender() override {}
        void OnMenuRender() override;

    private:
        char newConfigName[64];
        char importData[2048];
        std::string selectedConfig;
        std::string configToExport;
        bool showCreate;
        bool showImport;
        bool showDelete;
        bool showExport;
    };
}
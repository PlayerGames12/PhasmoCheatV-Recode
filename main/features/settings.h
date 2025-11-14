#pragma once
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>
#include "../includes.h"

namespace PhasmoCheatV
{
    using SettingValue = std::variant<bool, int, float, std::string, ImColor>;

    class ConfigEntry
    {
    public:
        ConfigEntry(std::string name, SettingValue value) noexcept
            : EntryName(std::move(name)), EntryValue(std::move(value))
        {
        }

        [[nodiscard]] std::string_view GetEntryName() const noexcept { return EntryName; }
        [[nodiscard]] const auto& GetEntryValue() const noexcept { return EntryValue; }
        auto& GetEntryValue() noexcept { return EntryValue; }

        void SetEntryValue(const auto& value) noexcept { EntryValue = value; }

    private:
        std::string EntryName;
        SettingValue EntryValue;
    };

    class ConfigManager
    {
    public:
        ConfigManager() { ConfigList.reserve(20); }

        void AddConfig(std::shared_ptr<ConfigEntry> config)
        {
            ConfigList.emplace_back(std::move(config));
            ConfigMap.emplace(ConfigList.back()->GetEntryName(), ConfigList.size() - 1);
        }

        [[nodiscard]] const auto& GetAllConfigs() const noexcept { return ConfigList; }

        [[nodiscard]] const auto& GetConfig(const std::string_view name) const
        {
            if (const auto it = ConfigMap.find(name); it != ConfigMap.end())
            {
                return ConfigList[it->second];
            }
            throw std::runtime_error("Config not found");
        }

        template<typename T>
        [[nodiscard]] T GetConfigValue(const std::string_view name) const
        {
            return std::get<T>(GetConfig(name)->GetEntryValue());
        }

        template<typename T>
        void SetConfigValue(const std::string_view name, const T& value)
        {
            GetConfig(name)->SetEntryValue(value);
        }

    private:
        std::vector<std::shared_ptr<ConfigEntry>> ConfigList;
        std::unordered_map<std::string_view, size_t> ConfigMap;
    };

#define DECLARE_CONFIG(Manager, Name, Type, DefaultValue) \
        Manager->AddConfig(std::make_shared<ConfigEntry>(Name, DefaultValue))

#define GET_CONFIG_VALUE(Manager, Name, Type) \
        Manager->GetConfigValue<Type>(Name)

#define SET_CONFIG_VALUE(Manager, Name, Type, Value) \
        Manager->SetConfigValue<Type>(Name, Value)

#define CONFIG_BOOL(Manager, Name) \
        GET_CONFIG_VALUE(Manager, Name, bool)

#define CONFIG_INT(Manager, Name) \
        GET_CONFIG_VALUE(Manager, Name, int)

#define CONFIG_FLOAT(Manager, Name) \
        GET_CONFIG_VALUE(Manager, Name, float)

#define CONFIG_STRING(Manager, Name) \
        GET_CONFIG_VALUE(Manager, Name, std::string)

#define CONFIG_COLOR(Manager, Name) \
        GET_CONFIG_VALUE(Manager, Name, ImColor)
}
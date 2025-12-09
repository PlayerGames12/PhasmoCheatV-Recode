#include <chrono>
#include <sstream>
#include <iomanip>
#include "config.h"

namespace PhasmoCheatV::Config
{
    void MergeConfigWithDefaults(nlohmann::json& existingConfig)
    {
        nlohmann::json defaultConfig;

        defaultConfig["menu_settings"] = {
            {"toggle_key", Globals::MenuToggleKey}
        };

        if (GET_FEATURE_HANDLER())
        {
            for (const auto& featurePair : GET_FEATURE_HANDLER()->GetFeatures())
            {
                const auto& name = featurePair.first;
                const auto& feature = featurePair.second;

                auto configManager = feature->GetConfigManager();
                nlohmann::json featureJson;

                for (const auto& config : configManager->GetAllConfigs())
                {
                    const auto& configName = config->GetEntryName();
                    const auto& value = config->GetEntryValue();

                    if (std::holds_alternative<bool>(value))
                    {
                        featureJson[configName] = std::get<bool>(value);
                    }
                    else if (std::holds_alternative<int>(value))
                    {
                        featureJson[configName] = std::get<int>(value);
                    }
                    else if (std::holds_alternative<float>(value))
                    {
                        featureJson[configName] = std::get<float>(value);
                    }
                    else if (std::holds_alternative<std::string>(value))
                    {
                        featureJson[configName] = std::get<std::string>(value);
                    }
                    else if (std::holds_alternative<ImColor>(value))
                    {
                        auto color = std::get<ImColor>(value);
                        featureJson[configName] = nlohmann::json{
                            {"r", color.Value.x},
                            {"g", color.Value.y},
                            {"b", color.Value.z},
                            {"a", color.Value.w}
                        };
                    }
                }

                defaultConfig[name] = featureJson;
            }
        }

        std::function<void(nlohmann::json&, const nlohmann::json&)> mergeRecursive =
            [&mergeRecursive](nlohmann::json& target, const nlohmann::json& source)
            {
                if (!source.is_object() || !target.is_object())
                    return;

                for (auto it = source.begin(); it != source.end(); ++it)
                {
                    const auto& key = it.key();
                    const auto& sourceValue = it.value();

                    if (!target.contains(key))
                    {
                        target[key] = sourceValue;
                    }
                    else if (sourceValue.is_object() && target[key].is_object())
                    {
                        mergeRecursive(target[key], sourceValue);
                    }
                }

                auto targetIt = target.begin();
                while (targetIt != target.end())
                {
                    if (!source.contains(targetIt.key()))
                    {
                        targetIt = target.erase(targetIt);
                    }
                    else
                    {
                        ++targetIt;
                    }
                }
            };

        mergeRecursive(existingConfig, defaultConfig);
    }

    void LoadConfigFromFile(const std::string& filePath)
    {
        Utils::CreatePhasmoCheatVDirectory();

        using Json = nlohmann::json;

        if (!std::filesystem::exists(filePath))
        {
            SaveConfigToFile(filePath);
            return;
        }

        try
        {
            std::ifstream f(filePath);

            if (f.peek() == std::ifstream::traits_type::eof())
            {
                f.close();
                SaveConfigToFile(filePath);
                return;
            }

            Json data = Json::parse(f);
            f.close();

            MergeConfigWithDefaults(data);

            if (data.contains("menu_settings") && data["menu_settings"].contains("toggle_key"))
            {
                Globals::MenuToggleKey = data["menu_settings"]["toggle_key"].get<int>();
            }

            if (GET_FEATURE_HANDLER())
            {
                for (const auto& featurePair : GET_FEATURE_HANDLER()->GetFeatures())
                {
                    const auto& name = featurePair.first;
                    const auto& feature = featurePair.second;

                    auto configManager = feature->GetConfigManager();

                    if (data.contains(name))
                    {
                        for (const auto& configName : configManager->GetAllConfigs())
                        {
                            const auto& config = configName->GetEntryName();

                            if (data[name].contains(config))
                            {
                                const auto& configValue = data[name][config];
                                auto& value = configName->GetEntryValue();

                                if (std::holds_alternative<bool>(value) && configValue.is_boolean())
                                {
                                    configName->SetEntryValue(configValue.get<bool>());
                                }
                                else if (std::holds_alternative<int>(value) && configValue.is_number_integer())
                                {
                                    configName->SetEntryValue(configValue.get<int>());
                                }
                                else if (std::holds_alternative<float>(value) && configValue.is_number_float())
                                {
                                    configName->SetEntryValue(configValue.get<float>());
                                }
                                else if (std::holds_alternative<std::string>(value) && configValue.is_string())
                                {
                                    configName->SetEntryValue(configValue.get<std::string>());
                                }
                                else if (std::holds_alternative<ImColor>(value) && configValue.is_object())
                                {
                                    ImColor color(
                                        configValue["r"].get<float>(),
                                        configValue["g"].get<float>(),
                                        configValue["b"].get<float>(),
                                        configValue["a"].get<float>()
                                    );
                                    configName->SetEntryValue(color);
                                }
                            }
                        }
                    }
                }
            }

            std::ofstream outFile(filePath);
            outFile << data.dump(4);
            outFile.close();
        }
        catch (const nlohmann::json::parse_error& e)
        {
            SaveConfigToFile(filePath);
        }
        catch (const std::exception& e) {}
    }

    void SaveConfigToFile(const std::string& filePath)
    {
        using Json = nlohmann::json;
        Json data;

        Json menuSettings;
        menuSettings["toggle_key"] = Globals::MenuToggleKey;
        data["menu_settings"] = menuSettings;

        if (GET_FEATURE_HANDLER())
        {
            for (const auto& featurePair : GET_FEATURE_HANDLER()->GetFeatures())
            {
                const auto& name = featurePair.first;
                const auto& feature = featurePair.second;

                auto configManager = feature->GetConfigManager();
                Json featureJson;

                for (const auto& config : configManager->GetAllConfigs())
                {
                    const auto& configName = config->GetEntryName();
                    const auto& value = config->GetEntryValue();

                    if (std::holds_alternative<bool>(value))
                    {
                        featureJson[configName] = std::get<bool>(value);
                    }
                    else if (std::holds_alternative<int>(value))
                    {
                        featureJson[configName] = std::get<int>(value);
                    }
                    else if (std::holds_alternative<float>(value))
                    {
                        featureJson[configName] = std::get<float>(value);
                    }
                    else if (std::holds_alternative<std::string>(value))
                    {
                        featureJson[configName] = std::get<std::string>(value);
                    }
                    else if (std::holds_alternative<ImColor>(value))
                    {
                        auto color = std::get<ImColor>(value);
                        featureJson[configName] = Json{
                            {"r", color.Value.x},
                            {"g", color.Value.y},
                            {"b", color.Value.z},
                            {"a", color.Value.w}
                        };
                    }
                }

                data[name] = featureJson;
            }
        }

        std::ofstream f(filePath);
        f << data.dump(4);
        f.close();
    }

    void LoadConfig()
    {
        const auto configPath = Utils::GetPhasmoCheatVDirectory() + "\\config.json";
        LoadConfigFromFile(configPath);
    }

    void SaveConfig()
    {
        const auto configPath = Utils::GetPhasmoCheatVDirectory() + "\\config.json";
        SaveConfigToFile(configPath);
    }
}

namespace PhasmoCheatV::ConfigsM
{
    static std::vector<ConfigInfo> g_Configs;
    static std::string g_ConfigsDir;

    std::string base64_encode(const std::string& input)
    {
        static const char* chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string output;
        output.reserve(((input.size() + 2) / 3) * 4);

        for (size_t i = 0; i < input.size(); i += 3)
        {
            uint32_t triple = (static_cast<uint32_t>(input[i]) << 16);
            if (i + 1 < input.size()) triple |= (static_cast<uint32_t>(input[i + 1]) << 8);
            if (i + 2 < input.size()) triple |= static_cast<uint32_t>(input[i + 2]);

            output += chars[(triple >> 18) & 0x3F];
            output += chars[(triple >> 12) & 0x3F];
            output += (i + 1 < input.size()) ? chars[(triple >> 6) & 0x3F] : '=';
            output += (i + 2 < input.size()) ? chars[triple & 0x3F] : '=';
        }

        return output;
    }

    std::string base64_decode(const std::string& input)
    {
        static std::vector<int> table(256, -1);
        static bool initialized = false;

        if (!initialized)
        {
            const char* chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            for (int i = 0; i < 64; i++)
                table[chars[i]] = i;
            initialized = true;
        }

        std::string output;
        output.reserve((input.size() * 3) / 4);

        uint32_t triple = 0;
        int bits = 0;

        for (char c : input)
        {
            if (c == '=') break;
            if (table[c] == -1) continue;

            triple = (triple << 6) | table[c];
            bits += 6;

            if (bits >= 8)
            {
                bits -= 8;
                output += static_cast<char>((triple >> bits) & 0xFF);
            }
        }

        return output;
    }

    void InitializeConfigs()
    {
        std::string baseDir = Utils::GetPhasmoCheatVDirectory();
        g_ConfigsDir = baseDir + "\\configs";
        std::filesystem::create_directories(g_ConfigsDir);
        RefreshConfigs();
    }

    void RefreshConfigs()
    {
        g_Configs.clear();

        if (!std::filesystem::exists(g_ConfigsDir))
            return;

        for (const auto& entry : std::filesystem::directory_iterator(g_ConfigsDir))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".json")
            {
                ConfigInfo info;
                info.filename = entry.path().filename().string();
                info.name = entry.path().stem().string();
                info.size = entry.file_size();

                auto ftime = std::filesystem::last_write_time(entry);
                auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                    ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
                std::time_t time = std::chrono::system_clock::to_time_t(sctp);

                std::stringstream ss;
                std::tm tm{};
                localtime_s(&tm, &time);
                ss << std::put_time(&tm, "%Y-%m-%d %H:%M");
                info.modifiedDate = ss.str();

                g_Configs.push_back(info);
            }
        }

        std::sort(g_Configs.begin(), g_Configs.end(),
            [](const ConfigInfo& a, const ConfigInfo& b) { return a.name < b.name; });
    }

    std::vector<ConfigInfo> GetConfigs()
    {
        return g_Configs;
    }

    bool LoadConfig(const std::string& name)
    {
        try
        {
            std::string configPath = g_ConfigsDir + "\\" + name + ".json";
            if (!std::filesystem::exists(configPath))
                return false;

            auto currentConfig = Utils::GetPhasmoCheatVDirectory() + "\\config.json";

            std::filesystem::copy_file(configPath, currentConfig, std::filesystem::copy_options::overwrite_existing);

            Config::LoadConfigFromFile(currentConfig);

            return true;
        }
        catch (const std::exception& e)
        {
            return false;
        }
    }

    bool SaveConfig(const std::string& name)
    {
        try
        {
            if (!std::filesystem::exists(g_ConfigsDir))
                std::filesystem::create_directories(g_ConfigsDir);

            std::string configPath = g_ConfigsDir + "\\" + name + ".json";

            Config::SaveConfig();

            std::string defaultConfig = Utils::GetPhasmoCheatVDirectory() + "\\config.json";
            if (std::filesystem::exists(defaultConfig))
            {
                std::filesystem::copy_file(defaultConfig, configPath, std::filesystem::copy_options::overwrite_existing);
                RefreshConfigs();
                return true;
            }
            return false;
        }
        catch (const std::exception& e)
        {
            return false;
        }
    }

    bool DeleteConfig(const std::string& name)
    {
        try
        {
            std::string configPath = g_ConfigsDir + "\\" + name + ".json";
            if (!std::filesystem::exists(configPath))
                return false;

            std::filesystem::remove(configPath);
            RefreshConfigs();
            return true;
        }
        catch (const std::exception& e)
        {
            return false;
        }
    }

    std::string ExportConfig(const std::string& name)
    {
        try
        {
            std::string configPath = g_ConfigsDir + "\\" + name + ".json";
            if (!std::filesystem::exists(configPath))
                return "";

            std::ifstream file(configPath, std::ios::binary);
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();

            std::string data = "PHASMOCHEATV:" + name + ":" + content;
            return base64_encode(data);
        }
        catch (const std::exception& e)
        {
            return "";
        }
    }

    bool ImportConfig(const std::string& data)
    {
        try
        {
            std::string decoded = base64_decode(data);

            if (decoded.find("PHASMOCHEATV:") != 0)
                return false;

            size_t nameStart = 13;
            size_t nameEnd = decoded.find(':', nameStart);
            if (nameEnd == std::string::npos)
                return false;

            std::string name = decoded.substr(nameStart, nameEnd - nameStart);
            std::string content = decoded.substr(nameEnd + 1);

            nlohmann::json testJson;
            try
            {
                testJson = nlohmann::json::parse(content);
            }
            catch (...)
            {
                return false;
            }

            std::string configPath = g_ConfigsDir + "\\" + name + ".json";

            Config::MergeConfigWithDefaults(testJson);

            std::ofstream file(configPath, std::ios::binary);
            file << testJson.dump(4);
            file.close();

            RefreshConfigs();
            return true;
        }
        catch (const std::exception& e)
        {
            return false;
        }
    }

    bool ConfigExists(const std::string& name)
    {
        std::string configPath = g_ConfigsDir + "\\" + name + ".json";
        return std::filesystem::exists(configPath);
    }
}
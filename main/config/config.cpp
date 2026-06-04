#include <chrono>
#include <sstream>
#include <iomanip>
#include "config.h"
#include "../menu/effects/custom_background.h"

namespace PhasmoCheatV::Config
{
    void MergeConfigWithDefaults(nlohmann::json& existingConfig)
    {
        nlohmann::json defaultConfig;

        defaultConfig["menu_settings"] = {
            {"toggle_key", Globals::MenuToggleKey},
            {"menu_blur", Globals::IsMenuBlur},
            {"menu_rain", Globals::IsMenuRain},
            {"menu_petals", Globals::IsMenuPetals},
            {"menu_stars", Globals::IsMenuStars},
            {"menu_firefiles", Globals::IsMenuFireflies},
            {"discord_rpc", Globals::DiscordRPC},
			{"rpc_show_name", Globals::RPCShowName}
        };

        defaultConfig["globals_colors"] = {
            {"accentPurple", {
                {"r", Globals::accentPurple.x},
                {"g", Globals::accentPurple.y},
                {"b", Globals::accentPurple.z},
                {"a", Globals::accentPurple.w}
            }},
            {"darkerBg", {
                {"r", Globals::darkerBg.x},
                {"g", Globals::darkerBg.y},
                {"b", Globals::darkerBg.z},
                {"a", Globals::darkerBg.w}
            }},
            {"accentPurpleDark", {
                {"r", Globals::accentPurpleDark.x},
                {"g", Globals::accentPurpleDark.y},
                {"b", Globals::accentPurpleDark.z},
                {"a", Globals::accentPurpleDark.w}
            }},
            {"accentPurpleLight", {
                {"r", Globals::accentPurpleLight.x},
                {"g", Globals::accentPurpleLight.y},
                {"b", Globals::accentPurpleLight.z},
                {"a", Globals::accentPurpleLight.w}
            }},
            {"darkBg", {
                {"r", Globals::darkBg.x},
                {"g", Globals::darkBg.y},
                {"b", Globals::darkBg.z},
                {"a", Globals::darkBg.w}
            }},
            {"cardBg", {
                {"r", Globals::cardBg.x},
                {"g", Globals::cardBg.y},
                {"b", Globals::cardBg.z},
                {"a", Globals::cardBg.w}
            }},
            {"headerBg", {
                {"r", Globals::headerBg.x},
                {"g", Globals::headerBg.y},
                {"b", Globals::headerBg.z},
                {"a", Globals::headerBg.w}
            }}
        };

        defaultConfig["custom_background"] =
        {
            {"enabled", CustomBackground::Enabled},
            {"selected_file", CustomBackground::SelectedFile},
            {"mode", (int)CustomBackground::Mode},
            {"scale", (int)CustomBackground::Scale},
            {"opacity", CustomBackground::Opacity},
            {"user_scale", CustomBackground::UserScale},
            {"offset_x", CustomBackground::Offset.x},
            {"offset_y", CustomBackground::Offset.y}
        };

        nlohmann::json bindsJson;
        for (const auto& [featureName, bind] : BindSystem::Binds)
        {
            bindsJson[featureName] = bind.Key;
        }
        defaultConfig["binds"] = bindsJson;

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

            if (data.contains("menu_settings"))
            {
                auto& m = data["menu_settings"];

                if (m.contains("toggle_key"))
                    Globals::MenuToggleKey = m["toggle_key"].get<int>();

                if (m.contains("menu_blur"))
                    Globals::IsMenuBlur = m["menu_blur"].get<bool>();

                if (m.contains("menu_rain"))
                    Globals::IsMenuRain = m["menu_rain"].get<bool>();

                if (m.contains("menu_petals"))
                    Globals::IsMenuPetals = m["menu_petals"].get<bool>();

                if (m.contains("menu_stars"))
                    Globals::IsMenuStars = m["menu_stars"].get<bool>();

                if (m.contains("menu_firefiles"))
                    Globals::IsMenuFireflies = m["menu_firefiles"].get<bool>();

				if (m.contains("discord_rpc"))
                    Globals::DiscordRPC = m["discord_rpc"].get<bool>();

				if (m.contains("rpc_show_name"))
                    Globals::RPCShowName = m["rpc_show_name"].get<bool>();
            }

            if (data.contains("globals_colors"))
            {
                auto& g = data["globals_colors"];

                auto loadColor = [](const nlohmann::json& j, ImVec4& color)
                    {
                        if (j.contains("r") && j.contains("g") && j.contains("b") && j.contains("a"))
                        {
                            color = ImVec4(
                                j["r"].get<float>(),
                                j["g"].get<float>(),
                                j["b"].get<float>(),
                                j["a"].get<float>()
                            );
                        }
                    };

                if (g.contains("accentPurple")) loadColor(g["accentPurple"], Globals::accentPurple);
                if (g.contains("darkerBg")) loadColor(g["darkerBg"], Globals::darkerBg);
                if (g.contains("accentPurpleDark")) loadColor(g["accentPurpleDark"], Globals::accentPurpleDark);
                if (g.contains("accentPurpleLight")) loadColor(g["accentPurpleLight"], Globals::accentPurpleLight);
                if (g.contains("darkBg")) loadColor(g["darkBg"], Globals::darkBg);
                if (g.contains("cardBg")) loadColor(g["cardBg"], Globals::cardBg);
                if (g.contains("headerBg")) loadColor(g["headerBg"], Globals::headerBg);
            }

            if (data.contains("custom_background"))
            {
                auto& bg = data["custom_background"];

                if (bg.contains("enabled"))
                    CustomBackground::Enabled = bg["enabled"].get<bool>();

                if (bg.contains("selected_file"))
                    CustomBackground::SelectedFile = bg["selected_file"].get<std::string>();

                if (bg.contains("mode"))
                    CustomBackground::Mode =
                    (CustomBackground::DrawMode)bg["mode"].get<int>();

                if (bg.contains("scale"))
                    CustomBackground::Scale =
                    (CustomBackground::ScaleMode)bg["scale"].get<int>();

                if (bg.contains("opacity"))
                    CustomBackground::Opacity = bg["opacity"].get<float>();

                if (bg.contains("user_scale"))
                    CustomBackground::UserScale = bg["user_scale"].get<float>();

                if (bg.contains("offset_x"))
                    CustomBackground::Offset.x = bg["offset_x"].get<float>();

                if (bg.contains("offset_y"))
                    CustomBackground::Offset.y = bg["offset_y"].get<float>();
            }

            if (data.contains("binds"))
            {
                for (auto& [featureName, key] : data["binds"].items())
                {
                    if (key.is_number_integer())
                    {
                        BindSystem::Binds[featureName].Key = key.get<int>();
                    }
                }
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
                        for (const auto& config : configManager->GetAllConfigs())
                        {
                            const auto& configName = config->GetEntryName();

                            if (data[name].contains(configName))
                            {
                                const auto& configValue = data[name][configName];
                                auto& value = config->GetEntryValue();

                                if (std::holds_alternative<bool>(value) && configValue.is_boolean())
                                {
                                    config->SetEntryValue(configValue.get<bool>());
                                }
                                else if (std::holds_alternative<int>(value) && configValue.is_number_integer())
                                {
                                    config->SetEntryValue(configValue.get<int>());
                                }
                                else if (std::holds_alternative<float>(value) && configValue.is_number_float())
                                {
                                    config->SetEntryValue(configValue.get<float>());
                                }
                                else if (std::holds_alternative<std::string>(value) && configValue.is_string())
                                {
                                    config->SetEntryValue(configValue.get<std::string>());
                                }
                                else if (std::holds_alternative<ImColor>(value) && configValue.is_object())
                                {
                                    ImColor color(
                                        configValue["r"].get<float>(),
                                        configValue["g"].get<float>(),
                                        configValue["b"].get<float>(),
                                        configValue["a"].get<float>()
                                    );
                                    config->SetEntryValue(color);
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
        menuSettings["menu_blur"] = Globals::IsMenuBlur;
        menuSettings["menu_rain"] = Globals::IsMenuRain;
        menuSettings["menu_petals"] = Globals::IsMenuPetals;
        menuSettings["menu_stars"] = Globals::IsMenuStars;
        menuSettings["menu_firefiles"] = Globals::IsMenuFireflies;
		menuSettings["discord_rpc"] = Globals::DiscordRPC;  
        menuSettings["rpc_show_name"] = Globals::RPCShowName;
        data["menu_settings"] = menuSettings;

        Json globalsColors;
        auto saveColor = [](const ImVec4& c)
            {
                return Json{
                    {"r", c.x},
                    {"g", c.y},
                    {"b", c.z},
                    {"a", c.w}
                };
            }; 
        globalsColors["accentPurple"] = saveColor(Globals::accentPurple);
        globalsColors["darkerBg"] = saveColor(Globals::darkerBg);
        globalsColors["accentPurpleDark"] = saveColor(Globals::accentPurpleDark);
        globalsColors["accentPurpleLight"] = saveColor(Globals::accentPurpleLight);
        globalsColors["darkBg"] = saveColor(Globals::darkBg);
        globalsColors["cardBg"] = saveColor(Globals::cardBg);
        globalsColors["headerBg"] = saveColor(Globals::headerBg);
        data["globals_colors"] = globalsColors;

        Json customBackground;
        customBackground["enabled"] = CustomBackground::Enabled;
        customBackground["selected_file"] = CustomBackground::SelectedFile;
        customBackground["mode"] = (int)CustomBackground::Mode;
        customBackground["scale"] = (int)CustomBackground::Scale;
        customBackground["opacity"] = CustomBackground::Opacity;
        customBackground["user_scale"] = CustomBackground::UserScale;
        customBackground["offset_x"] = CustomBackground::Offset.x;
        customBackground["offset_y"] = CustomBackground::Offset.y;
        data["custom_background"] = customBackground;

        Json bindsJson;
        for (const auto& [featureName, bind] : BindSystem::Binds)
        {
            bindsJson[featureName] = bind.Key;
        }
        data["binds"] = bindsJson;

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

    static std::string miniz_compress(const std::string& input)
    {
        if (input.empty()) return "";

        mz_ulong destLen = mz_compressBound(static_cast<mz_ulong>(input.size()));
        std::vector<unsigned char> compressed(destLen);

        int ret = mz_compress(compressed.data(), &destLen,
            reinterpret_cast<const unsigned char*>(input.data()),
            static_cast<mz_ulong>(input.size()));

        if (ret != MZ_OK) return "";
        compressed.resize(destLen);
        return std::string(reinterpret_cast<char*>(compressed.data()), destLen);
    }

    static std::string miniz_decompress(const std::string& compressed)
    {
        if (compressed.empty()) return "";

        mz_ulong destLen = compressed.size() * 4;
        std::vector<unsigned char> decompressed;

        int ret;
        do
        {
            decompressed.resize(destLen);
            mz_ulong actualLen = destLen;

            ret = mz_uncompress(decompressed.data(), &actualLen,
                reinterpret_cast<const unsigned char*>(compressed.data()),
                static_cast<mz_ulong>(compressed.size()));

            if (ret == MZ_OK)
            {
                decompressed.resize(actualLen);
                return std::string(reinterpret_cast<char*>(decompressed.data()), actualLen);
            }

            if (ret != MZ_BUF_ERROR) return "";
            destLen *= 2;
        } while (destLen < 10 * 1024 * 1024);

        return "";
    }

    static std::string compress_and_z85(const std::string& original)
    {
        if (original.empty()) return "";
        std::string compressed = miniz_compress(original);
        if (compressed.empty()) return "";

        size_t bound = Z85_encode_with_padding_bound(compressed.size());
        std::vector<char> encoded(bound + 1, '\0');

        size_t encoded_len = Z85_encode_with_padding(compressed.data(), encoded.data(), compressed.size());
        return encoded_len ? std::string(encoded.data(), encoded_len) : "";
    }

    static std::string z85_decode_and_decompress(const std::string& encoded)
    {
        if (encoded.empty()) return "";

        size_t max_decoded = (encoded.size() * 4 / 5) + 8;
        std::vector<char> bin(max_decoded);

        size_t bin_len = Z85_decode_with_padding(encoded.data(), bin.data(), encoded.size());
        if (bin_len == 0) return "";

        std::string compressed_bin(bin.data(), bin_len);
        return miniz_decompress(compressed_bin);
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
            return compress_and_z85(data);
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
            std::string decoded = z85_decode_and_decompress(data);
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
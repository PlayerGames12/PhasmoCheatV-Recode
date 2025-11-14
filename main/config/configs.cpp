#include "configs.h"
#include "config.h"
#include <chrono>
#include <sstream>
#include <iomanip>

namespace PhasmoCheatV::ConfigsM
{
    static std::vector<ConfigInfo> g_Configs;
    static std::string g_ConfigsDir;

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
                ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M");
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
            auto backupConfig = Utils::GetPhasmoCheatVDirectory() + "\\config_backup.json";

            if (std::filesystem::exists(currentConfig))
                std::filesystem::copy_file(currentConfig, backupConfig, std::filesystem::copy_options::overwrite_existing);

            std::filesystem::copy_file(configPath, currentConfig, std::filesystem::copy_options::overwrite_existing);
            Config::LoadConfig();

            if (std::filesystem::exists(backupConfig))
            {
                std::filesystem::copy_file(backupConfig, currentConfig, std::filesystem::copy_options::overwrite_existing);
                std::filesystem::remove(backupConfig);
            }

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
            std::string defaultConfig = Utils::GetPhasmoCheatVDirectory() + "\\config.json";

            Config::SaveConfig();

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

            std::string configPath = g_ConfigsDir + "\\" + name + ".json";
            std::ofstream file(configPath, std::ios::binary);
            file << content;
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
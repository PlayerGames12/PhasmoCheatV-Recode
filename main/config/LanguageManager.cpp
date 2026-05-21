#include "LanguageManager.h"
#include "../Includes.h"
#include <fstream>
#include <algorithm>
#include "Translations.h"
#include "../menu/styles.h"
 
namespace PhasmoCheatV {

    Language LanguageManager::currentLanguage = Language::EN;
    std::unordered_map<std::string, TranslationEntry> LanguageManager::translations;
    bool LanguageManager::isInitialized = false;

    std::string LanguageManager::GetLanguagePath() {
        return Utils::GetPhasmoCheatVDirectory() + "\\Language.json";
    }

    void LanguageManager::Init() {
        if (isInitialized) return;

        ::RegisterAllTranslations();

        LoadFromJSON();

        auto translatePath = Utils::GetPhasmoCheatVDirectory() + "\\Translate.json"; 
        if (!std::filesystem::exists(translatePath)) {
            try {
                nlohmann::json example;
                example["LKEY"] = { {"EN", "English text"}, {"RU", "Russian text"} };

                std::ofstream out(translatePath);
                out << example.dump(4);
            }
            catch (...) {
                LOG_ERROR("Failed to create Translate.json with example");
            }
        }

        LoadCustomOverrides();

        isInitialized = true;
    }

    void LanguageManager::AddString(const std::string& key, const std::string& en, const char8_t* ru_utf8, const char8_t* zh_utf8) {
        std::string ru(reinterpret_cast<const char*>(ru_utf8));
        std::string zh(reinterpret_cast<const char*>(zh_utf8));

        if (translations.find(key) == translations.end()) {
            translations[key] = { en, ru, zh };
        }
        else {
            translations[key] = { en, ru, zh };
        }
    }

    const char* LanguageManager::Get(const std::string& key) {
        if (!isInitialized || translations.empty()) {
            Init();
        }

        auto it = translations.find(key);
        if (it != translations.end()) {
            const auto& entry = it->second;

            switch (currentLanguage) {
            case Language::EN:
                return entry.en.c_str();

            case Language::RU:
                return entry.ru.c_str();

            case Language::ZH:
                if (!entry.zh.empty())
                    return entry.zh.c_str();
                else {
                    static std::string temp;
                    temp = "China not supported..##" + key;
                    return temp.c_str();
                }
            }
        }

        return key.c_str();
    }

    void LanguageManager::SetLanguage(Language lang) {
        currentLanguage = lang;
    }
     
    void LanguageManager::SetLanguage(const std::string& langCode) {
        std::string upper = langCode;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);

        if (upper == "RU") currentLanguage = Language::RU;
        else if (upper == "ZH" || upper == "CN") currentLanguage = Language::ZH;
        else currentLanguage = Language::EN;
    }

    void LanguageManager::SaveLanguage() {
        try {
            nlohmann::json data;
            data["language"] = (currentLanguage == Language::RU ? "RU" : currentLanguage == Language::ZH ? "ZH" : "EN");

            std::ofstream out(GetLanguagePath());
            out << data.dump(4);
        }
        catch (...) {}
    }

    void LanguageManager::LoadFromJSON() {
        try {
            auto path = GetLanguagePath();
            if (!std::filesystem::exists(path)) return;

            std::ifstream f(path);
            if (!f.good() || f.peek() == EOF) return;

            nlohmann::json data;
            f >> data;

            if (data.contains("language")) {
                SetLanguage(data["language"].get<std::string>());
            }
        }
        catch (...) {
        }
    }

    void LanguageManager::LoadCustomOverrides() {
        try {
            auto path = Utils::GetPhasmoCheatVDirectory() + "\\Translate.json";
            if (!std::filesystem::exists(path)) return;

            std::ifstream f(path);
            if (!f.good() || f.peek() == EOF) return;

            nlohmann::json customData;
            f >> customData;

            for (auto& [key, translationsObj] : customData.items()) {
                std::string en = translationsObj.value("EN", "");
                std::string ru = translationsObj.value("RU", "");
                std::string zh = translationsObj.value("ZH", "");

                if (!en.empty() || !ru.empty() || !zh.empty()) {
                    translations[key] = { en, ru, zh };
                }
            }
        }
        catch (...) {
        }
    }

    Language LanguageManager::GetCurrentLanguage() {
        return currentLanguage;
    }
}
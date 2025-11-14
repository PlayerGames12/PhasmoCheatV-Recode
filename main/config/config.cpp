#include "config.h"

namespace PhasmoCheatV::Config
{
	void LoadConfig()
	{
		Utils::CreatePhasmoCheatVDirectory();

		using Json = nlohmann::json;
		const auto configPath = Utils::GetPhasmoCheatVDirectory() + "\\config.json";

		if (!std::filesystem::exists(configPath))
			return;

		std::ifstream f(configPath);
		Json data = Json::parse(f);

		if (data.contains("menu_settings"))
		{
			const auto& menuSettings = data["menu_settings"];
			if (menuSettings.contains("toggle_key"))
			{
				Globals::MenuToggleKey = menuSettings["toggle_key"].get<int>();
			}
		}

		if (GET_FEATURE_HANDLER())
		{
			for (const auto& [name, feature] : GET_FEATURE_HANDLER()->GetFeatures())
			{
				auto configManager = feature->GetConfigManager();
				if (!data.contains(name))
					continue;

				for (const auto& configName : configManager->GetAllConfigs())
				{
					const auto& config = configName->GetEntryName();
					if (!data[name].contains(config))
						continue;

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

		f.close();
	}

	void SaveConfig()
	{
		const auto configPath = Utils::GetPhasmoCheatVDirectory() + "\\config.json";

		using Json = nlohmann::json;
		Json data;

		Json menuSettings;
		menuSettings["toggle_key"] = Globals::MenuToggleKey;
		data["menu_settings"] = menuSettings;

		if (GET_FEATURE_HANDLER())
		{
			for (const auto& [name, feature] : GET_FEATURE_HANDLER()->GetFeatures())
			{
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

		std::ofstream f(configPath);
		f << data.dump(4);
		f.close();
	}
}
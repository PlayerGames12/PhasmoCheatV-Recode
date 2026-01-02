#pragma once
#include "sdk.h"

namespace SDK
{
	enum WeatherType : int32_t
	{
		clear,
		foggy,
		rain,
		heavyRain,
		snow,
		wind,
		sunrise,
		bloodMoon,
		dead
	};

	struct WeatherProfileFields
	{
		char pad_000[0x8]; // ScriptableObjectFields
		void* azureProfile;
		WeatherType weatherType;
		// more
	};

	struct WeatherProfile
	{ 
		void* Clazz;
		void* Monitor;
		WeatherProfileFields Fields;
	};
}
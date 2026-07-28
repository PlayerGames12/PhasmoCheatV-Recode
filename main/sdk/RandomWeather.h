#pragma once
#include "sdk.h"

namespace SDK
{
	struct RandomWeatherFields
	{
		MonoBehaviourFields monoBehaviourFields;
		void* weather;
		void* environment;
		void* time;
		void* effects;
		void* sky;
		void* weatherParticles;
		void* cameraNightVisionPostProcess;
		void* transitionPP;
		void* transitionAudio;
		void* directionalLight;
		void* allWeatherProfiles;
		void* deadWeatherProfile;
		WeatherProfile* currentWeatherProfile;
		bool disableWeatherParticlesInBasement;
		void* OnWeatherChanging;
	};

	struct RandomWeather
	{
		void* Clazz;
		void* Monitor;
		RandomWeatherFields Fields;
	};

	struct RandomWeather_staticFields
	{
		RandomWeather* instance;
	};

	DEC_MET(RandomWeather_Start, void(*)(RandomWeather* randomWeather, MethodInfo* methodInfo), "Assembly-CSharp", "", "RandomWeather", "Start", 0);
	DEC_SFIELD(RandomWeather_sFields, RandomWeather_staticFields, "Assembly-CSharp", "", "RandomWeather");
}
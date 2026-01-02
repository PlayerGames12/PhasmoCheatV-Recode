#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkRandomWeather_Start(SDK::RandomWeather* randomWeather, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called RandomWeather_Start");

	if (CheatWork)
		InGame::randomWeather = randomWeather;

	SDK::RandomWeather_Start(randomWeather, methodInfo);
}
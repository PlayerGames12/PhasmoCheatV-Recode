#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkLightSwitch_Start(SDK::LightSwitch* lightSwitch, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called LightSwitch_Start");

	if (CheatWork)
		InGame::lightSwitchs.push_back(lightSwitch);

	SDK::LightSwitch_Start(lightSwitch, methodInfo);
}
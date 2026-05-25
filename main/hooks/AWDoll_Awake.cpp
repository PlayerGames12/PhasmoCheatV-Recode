#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkAWDoll_Awake(SDK::AWDoll* instance, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called AWDoll_Awake");

	if (CheatWork && instance)
		InGame::awDolls.push_back(instance);

	SDK::AWDoll_Awake(instance, methodInfo);
}
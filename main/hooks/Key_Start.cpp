#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkKey_Start(SDK::Key* key, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called Key_Start");

	InGame::keys.push_back(key);

	SDK::Key_Start(key, methodInfo);
}
#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

bool Hooks::hkLevelValues_IsPerfectGame(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called LevelValues_IsPerfectGame");

	return CALL_METHOD_ARGS(Misc, RewardModifier, RewardModifierMainPrefGame, levelValues, methodInfo);
}
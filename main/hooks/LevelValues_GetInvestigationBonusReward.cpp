#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

int32_t Hooks::hkLevelValues_GetInvestigationBonusReward(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called LevelValues_GetInvestigationBonusSynced");

    return CALL_METHOD_ARGS(Misc, RewardModifier, RewardModifierMainBonus, levelValues, methodInfo);
}
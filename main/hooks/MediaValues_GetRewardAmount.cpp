#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

int32_t Hooks::hkMediaValues_GetRewardAmount(SDK::MediaValues* mediaValues, SDK::EvidenceQualityType qualityType, SDK::TierList mediaTier, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called LevelValues_GetInvestigationBonus");

	return CALL_METHOD_ARGS(Misc, RewardModifier, RewardModifierMainMediaBonus, mediaValues, qualityType, mediaTier, methodInfo);
}
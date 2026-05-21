#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkRewardManager_Awake(SDK::RewardManager* rewardManager, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called RewardManager_Awake");

	if (CheatWork)
		InGame::rewardManager = rewardManager;
	
	SDK::RewardManager_Awake(rewardManager, methodInfo);
}
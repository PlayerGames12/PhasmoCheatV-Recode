#pragma once
#include "sdk.h"

namespace SDK
{
	struct RewardManagerFields
	{
		char* pad_000[0x188];
		bool isPlayerDead;
		int32_t totalReward;
		int32_t totalXp;
	};

	struct RewardManager
	{
		void* Clazz;
		void* Monitor;
		RewardManagerFields Fields;
	};

	DEC_MET(RewardManager_Next, void(*)(RewardManager* rewardManager, MethodInfo* methodInfo), "Assembly-CSharp", "", "RewardManager", "Next", 0);
	DEC_MET(RewardManager_Skip, void(*)(RewardManager* rewardManager, MethodInfo* methodInfo), "Assembly-CSharp", "", "RewardManager", "Skip", 0);
	DEC_MET(RewardManager_Awake, void(*)(RewardManager* rewardManager, MethodInfo* methodInfo), "Assembly-CSharp", "", "RewardManager", "Awake", 0);
}
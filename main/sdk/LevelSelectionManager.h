#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelSelectionManager;

	DEC_MET(LevelSelectionManager_Start, std::nullptr_t(*)(LevelSelectionManager* levelSelectionManager, MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelSelectionManager", "Start", 0);
	DEC_MET(LevelSelectionManager_VoteMap, void(*)(LevelSelectionManager* levelSelectionManager, int32_t mapID, MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelSelectionManager", "VoteMap", 1);
}
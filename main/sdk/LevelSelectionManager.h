#pragma once
#include "sdk.h"

namespace SDK
{
	struct ContractsArray
	{
		void* klass;
		void* monitor;
		void* bounds;
		uint32_t max_length;
		Contract* vector[1];
	};

	struct LevelSelectionManagerFields
	{
		MonoBehaviourFields monoBehaviourFields;
		void* totalRoomsText;
		void* totalFloorsText;
		ContractsArray* contracts;
		Contract* votedContract;
		void* mostVotedMaps;
	};

	struct LevelSelectionManager
	{
		void* Clazz;
		void* Monitor;
		LevelSelectionManagerFields Fields;
	};

	DEC_MET(LevelSelectionManager_Start, std::nullptr_t(*)(LevelSelectionManager* levelSelectionManager, MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelSelectionManager", "Start", 0);
	DEC_MET(LevelSelectionManager_VoteMap, void(*)(LevelSelectionManager* levelSelectionManager, int32_t mapID, MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelSelectionManager", "VoteMap", 1);
}
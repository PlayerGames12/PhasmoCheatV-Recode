#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelRoom;
	struct GhostAI;

	struct GhostInfoFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		GhostTraits GhostTraits;
		GhostAI* Ghost;
		LevelRoom* favouriteRoom;
		float activityMultiplier;
		bool hasSetEvidence;
	};

	struct GhostInfo
	{
		void* Clazz;
		void* Monitor;
		GhostInfoFields Fields;
	};

	DEC_MET(GhostInfo_SyncValuesNetworked, void(*)(GhostInfo* instance, int ghostType, int ghostAge, bool isMale, int ghostFirstNameID, int ghostLastNameID, bool isShy, int deathLength, int favouriteRoomID, bool isWhisper, void* photonMessageInfo, MethodInfo* methodinfo), "Assembly-CSharp", "", "GhostInfo", "SyncValuesNetworked", 10);

	DEC_MET(GhostInfo_SyncEvidence, void(*)(GhostInfo* instance, int* evidence, void* info, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostInfo", "SyncEvidence", 2);
}

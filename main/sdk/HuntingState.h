#pragma once
#include "sdk.h"

namespace SDK
{
	struct HuntingStateFields // all names in the fields is fake!
	{
		GhostAI* ghostAI;
		void* navMeshAgent;
		PhotonView* photonView;
		GameController* gameController;
		LevelController* levelController;
		void* soundController;
		int32_t ghostType;
		char pad_000[0x4];
		Player* playerToChase;
		Player* playerToCheck;
		Player* previousPlayer;
		Player* targetPlayer;
		void* playersTargettedByGhost;
		void* playersKilled;
		Vector3 lastKnownLocation;
		bool hasCheckedLastLocation;
		char pad_001[0x3];
		float huntDurationTimer;
		float Field7C;
		bool canHunt;
		bool hasKilledPlayer;
		bool cursedHunt;
		char pad_002[0x1];
		float doorInteractTimer;
		float doorCheckTimer;
		float propInteractTimer;
		float previousPlayerSearchTimer;
		float ghostAbilityTimer;
		float setGhostStartSpeedTimer;
		float playerInsideCheckDelay;
		float FieldA0;
		float huntSpeedModifier;
		float killDistance;
		float killOverrideBufferDistance;
		float killOverrideTimeout;
		float deogenOverrideMultiplier;
		float enteredkillBufferZoneTime;
		float FieldBC;
		void* closetZone;
	};

	struct HuntingState
	{
		void* Clazz;
		void* Monitor;
		HuntingStateFields Fields;
	};

	DECLARE_PATTERN_POINTER(HuntingState_ctor, void(*)(HuntingState* huntingState, GhostAI* ghostAI, void* navMeshAgent, PhotonView* photonView, bool force, MethodInfo* methodInfo), L"GameAssembly.dll", "il2cpp", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 80 3D ? ? ? ? 00 49 8B E9 4D 8B F0 48 8B F2 48 8B F9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 0D"); // 1 in HowFindMethods
}
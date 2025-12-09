#pragma once
#include "sdk.h"

namespace SDK
{
	struct Player;

	struct PlayerSanityFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* PhotonView;
		Player* Player;
		float insanity;
		float Field2;
		float Field3;
		void* Field4;
		bool Field5;
		float Field6;
		bool Field7;
		float Field8;
		float Field9;
		bool Field10;
		void* Field11;
	};

	struct PlayerSanity
	{
		void* Clazz;
		void* Monitor;
		PlayerSanityFields Fields;
	};

	DEC_MET(PlayerSanity_SetInsanity, void(*)(PlayerSanity* playerSanity, int insanity, MethodInfo* methodInfo), "Assembly-CSharp", "", "PlayerSanity", "SetInsanity", 1);
}

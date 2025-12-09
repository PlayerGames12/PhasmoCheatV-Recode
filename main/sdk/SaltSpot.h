#pragma once
#include "sdk.h"

namespace SDK 
{
	struct SaltSpotFields
	{
		MonoBehaviourPunFields monoBehaviourPunFields;
		GameObject* normalSalt;
		GameObject* flatSalt;
		void* saltSpray;
		Evidence* videoEvidence;
		bool used;
		void* tier;
	};

	struct SaltSpot
	{
		void* Clazz;
		void* Monitor;
		SaltSpotFields Fields;
	};

	DEC_MET(SaltSpot_SyncSalt, void(*)(SaltSpot* saltSpot, void* photonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "SaltSpot", "SyncSalt", 1);
}
#pragma once
#include "sdk.h"

namespace SDK
{
	struct String;
	struct MethodInfo;

	struct SaltShakerFields
	{
		char pad_000[0x1A8];
		void* saltClips;
		void* saltHelperObject;
		void* saltHelperVisual;
		int32_t uses;
		char pad_001[4];
		String* poolName;
		void* lidObject;
		void* visuals;
	};

	struct SaltShaker
	{
		void* Clazz;
		void* Monitor;
		SaltShakerFields Fields;
	};

	DEC_MET(SaltShaker_Update, void(*)(SaltShaker* saltShaker, MethodInfo* methodInfo), "Assembly-CSharp", "", "SaltShaker", "Update", 0);
}
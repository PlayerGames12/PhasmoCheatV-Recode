#pragma once
#include "sdk.h"

namespace SDK
{
	struct LightningControllerFields
	{
		MonoBehaviourPunFields monoBehaviourPunFields;
		void* effects;

	};

	struct LightningController
	{
		void* Clazz;
		void* Monitor;
		LightningControllerFields Fields;
	};

	DEC_MET(LightningController_Start, void(*)(LightningController* lightningController, MethodInfo* methodInfo), "Assembly-CSharp", "", "LightningController", "Start", 0);
	DECLARE_PATTERN_POINTER(LightningController_PlayLightning, void(*)(LightningController* lightningController, MethodInfo* methodInfo), L"GameAssembly.dll", "il2cpp", "40 53 48 83 EC ? 80 3D ? ? ? ? 00 48 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 33 C9 E8 ? ? ? ? 48 85 C0 74 ? 48 8B 80 ? ? ? ? 48 85 C0 74 ? 83 78 ? ? 75 ? 33 D2 48 8B CB E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D8 E8 ? ? ? ? 48 85 DB 74 ? 48 8B 15 ? ? ? ? 4C 8B C8 45 33 C0 48 C7 44 24 ? 00 00 00 00 48 8B CB E8 ? ? ? ? 48 83 C4 ? 5B C3 E8 ? ? ? ? ? ? ? ? ? ? ? ? ? ? 40 53 48 83 EC ? 45 33 C0 48 8B D9 41 8D 50 ? 41 8D 48");
}
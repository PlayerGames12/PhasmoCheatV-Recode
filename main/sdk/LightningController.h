#pragma once
#include "sdk.h"

namespace SDK
{
	struct AzureEffectsController;

	struct LightningControllerFields
	{
		MonoBehaviourPunFields monoBehaviourPunFields;
		AzureEffectsController* effects;
	};

	struct LightningController
	{
		void* Clazz;
		void* Monitor;
		LightningControllerFields Fields;
	};

	DEC_MET(LightningController_Start, void(*)(LightningController* lightningController, MethodInfo* methodInfo), "Assembly-CSharp", "", "LightningController", "Start", 0);
	DECLARE_PATTERN_POINTER(LightningController_PlayLightning, void(*)(LightningController* lightningController, MethodInfo* methodInfo), L"GameAssembly.dll", "il2cpp", ""); // 7 in HowFindMethods. // not used
}
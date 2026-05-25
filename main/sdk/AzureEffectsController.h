#pragma once
#include "sdk.h"

namespace SDK
{
	struct AzureEffectsControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* windZone;
		AudioSource* lightRainAudioSource;
		AudioSource* heavyRainAudioSource;
		AudioSource* heavyWindAudioSource;
	};

	struct AzureEffectsController
	{
		void* Clazz;
		void* Monitor;
		AzureEffectsControllerFields Fields;
	};
}
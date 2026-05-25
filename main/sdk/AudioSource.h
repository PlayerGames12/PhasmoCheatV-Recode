#pragma once
#include "sdk.h"

namespace SDK
{
	struct AudioSource;

	DEC_MET(AudioSource_get_volume, float(*)(AudioSource* audioSource, MethodInfo* methodInfo), "UnityEngine.AudioModule", "UnityEngine", "AudioSource", "get_volume", 0);
	DEC_MET(AudioSource_set_volume, void(*)(AudioSource* audioSource, float volume, MethodInfo* methodInfo), "UnityEngine.AudioModule", "UnityEngine", "AudioSource", "set_volume", 1);
}
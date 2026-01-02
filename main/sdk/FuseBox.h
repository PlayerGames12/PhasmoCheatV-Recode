#pragma once
#include "sdk.h"

namespace SDK
{
	struct FuseBoxFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		int32_t FuseBoxType;
		void* Rends;
		void* Lights; 
		void* VolumetricLights;
		void* LightPulse;
		void* RendsToTurnOff;
		void* LightSourcesWithoutSwitches;
		void* RotatingObjects;
		void* LoopSource;
		void* Noise;
		Transform* Field8;
		void* OnClip;
		void* OffClip;
		bool IsOn;
		LightSwitchArray* switches; // Not work. Always = 0
		void* PhotonInteract;
		int32_t currentOnLights;
		int32_t maxLights;
		Transform* MapIcon;
		Transform* ShakeObject;
		Transform* HandleObject;
		Vector3 HandleOnAngle;
		Vector3 HandleOffAngle;
		void* BrokenFuseBoxObject;
		bool Field22;
		void* Field23;
		void* Field24;
	};

	struct FuseBox
	{
		void* Clazz;
		void* Monitor;
		FuseBoxFields Fields;
	};

	DEC_MET(FuseBox_Start, void(*)(FuseBox* fuseBox, MethodInfo* methodInfo), "Assembly-CSharp", "", "FuseBox", "Start", 0);
	DEC_MET(FuseBox_Use, void(*)(FuseBox* fuseBox, MethodInfo* methodInfo), "Assembly-CSharp", "", "FuseBox", "Use", 0);
}

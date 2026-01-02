#pragma once
#include "sdk.h"

namespace SDK
{
	struct LightSwitch;

    struct LightSwitchArray
    {
        void* Clazz;
        void* Monitor;
        void* Bounds;
        void* MaxLength;
        LightSwitch* Vector[65535];
    };


	DEC_MET(LightSwitch_UseLightSwitch, void(*)(LightSwitch* lightSwitch, bool giveFingerprint, bool isGhostUse, bool isMareAbility, MethodInfo* methodInfo), "Assembly-CSharp", "", "LightSwitch", "UseLightSwitch", 3);
	DEC_MET(LightSwitch_Use, void(*)(LightSwitch* lightSwitch, bool on, bool giveFingerprint, bool isGhostUse, bool isMareAbility, MethodInfo* methodInfo), "Assembly-CSharp", "", "LightSwitch", "Use", 4);
    DEC_MET(LightSwitch_Start, void(*)(LightSwitch* lightSwitch, MethodInfo* methodInfo), "Assembly-CSharp", "", "LightSwitch", "Start", 0);
}
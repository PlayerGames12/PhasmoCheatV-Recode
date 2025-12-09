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
        uint32_t MaxLength;  // גלוסעמ void*
        LightSwitch* Vector[65535];
    };


	DEC_MET(LightSwitch_UseLightSwitch, void(*)(LightSwitch* lightSwitch, bool giveFingerprint, bool isGhostUse, bool isMareAbility, MethodInfo* methodInfo), "Assembly-CSharp", "", "LightSwitch", "UseLightSwitch", 3);

}
#pragma once
#include "sdk.h"

namespace SDK
{
	struct Key;

	DEC_MET(Key_Start, void(*)(Key* key, MethodInfo* methodInfo), "Assembly-CSharp", "", "Key", "Start", 0)
	DEC_MET(Key_GrabbedKey, void(*)(Key* key, MethodInfo* methodInfo), "Assembly-CSharp", "", "Key", "GrabbedKey", 0)
}

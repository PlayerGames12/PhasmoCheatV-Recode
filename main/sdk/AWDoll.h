#pragma once
#include "sdk.h"

namespace SDK
{
	struct AWDoll;

	DEC_MET(AWDoll_Awake, void(*)(AWDoll* awDoll, MethodInfo* methodInfo), "Assembly-CSharp", "", "AWDoll", "Awake", 0);
}
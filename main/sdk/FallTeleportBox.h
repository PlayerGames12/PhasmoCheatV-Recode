#pragma once
#include "sdk.h"

namespace SDK
{
	struct FallTeleportBox;

	DEC_MET(FallTeleportBox_OnTriggerEnter, void(*)(FallTeleportBox* fallTeleportBox, Collider* collider, MethodInfo* methodInfo), "Assembly-CSharp", "", "FallTeleportBox", "OnTriggerEnter", 1);
}

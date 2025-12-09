#pragma once
#include "sdk.h"

namespace SDK
{
	struct GhostActivity;

	DEC_MET(GhostActivity_GhostAbility, void(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostActivity", "GhostAbility", 0);
	DEC_MET(GhostActivity_TryInteract, void(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostActivity", "TryInteract", 0);
	DEC_MET(GhostActivity_InteractWithARandomDoor, bool(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostActivity", "InteractWithARandomDoor", 0);
	DEC_MET(GhostActivity_InteractWithRandomLightSwitch, bool(*)(GhostActivity* ghostActivity, bool force, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostActivity", "InteractWithRandomLightSwitch", 1);
	DEC_MET(GhostActivity_InteractWithARandomProp, void(*)(GhostActivity* ghostActivity, bool force, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostActivity", "InteractWithARandomProp", 1);
	DEC_MET(GhostActivity_NormalInteraction, void(*)(GhostActivity* ghostActivity, bool force, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostActivity", "NormalInteraction", 1);
	DEC_MET(GhostActivity_TwinInteraction, void(*)(GhostActivity* ghostActivity, bool force, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostActivity", "TwinInteraction", 1);
}

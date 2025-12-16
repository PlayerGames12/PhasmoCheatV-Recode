#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkFallTeleportBox_OnTriggerEnter(SDK::FallTeleportBox* fallTeleportBox, SDK::Collider* collider, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called FallTeleportBox_OnTriggerEnter");

	CALL_METHOD_ARGS(Movement, NoClip, NoClipOffTeleport, fallTeleportBox, collider, methodInfo);
}
#include "../Includes.h"
#include "../features/features_includes.h"

void Hooks::hkSaltSpot_SyncSalt(SDK::SaltSpot* saltSpot, void* photon, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Call SaltSpot_SyncSalt");

	CALL_METHOD_ARGS(Map, SaltModifier, SaltModifierMainNoUseGhost, saltSpot, photon, methodInfo);
}
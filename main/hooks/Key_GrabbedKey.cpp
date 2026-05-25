#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkKey_GrabbedKey(SDK::Key* key, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called Key_GrabbedKey");

	SDK::Key_GrabbedKey(key, methodInfo);

	if (CheatWork)
	{
		auto* keyInfo = key->Fields.info;
		if (!keyInfo) return;

		SDK::KeyType keyType = keyInfo->Fields.keyType;

		if (keyType == SDK::KeyType::Main)
		{
			CALL_METHOD(Map, DoorModifier, AutoOpenDoors);
			NOTIFY_SUCCESS_QUICK(LANG("AutoOpenDoors_Done"));
		}
	}
}
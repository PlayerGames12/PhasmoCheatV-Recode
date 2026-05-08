#include "grabkey.h"

using namespace PhasmoCheatV::Features::Map;

GrabKeys::GrabKeys() : FeatureCore(LANG("GrabKeys_Header"), TYPE_MAP)
{
	DECLARE_CONFIG(GetConfigManager(), "AutoGrabKeys", bool, false);
}

void GrabKeys::OnMenuRender()
{
	if (ImGui::Button(LANG("GrabAllKeys")))
	{
		GrabKeysAll();
	}
	bool autoGrabKeys = CONFIG_BOOL(GetConfigManager(), "AutoGrabKeys");
	if (ImGui::Checkbox(LANG("AutoGrabAllKeys"), &autoGrabKeys))
		SET_CONFIG_VALUE(GetConfigManager(), "AutoGrabKeys", bool, autoGrabKeys);
}

void GrabKeys::GrabKeysAll()
{
	if (InGame::keys.empty())
	{
		NOTIFY_ERROR_QUICK(LANG("NoKeysFound"));
		return;
	}

	uint32_t grabbed = 0;

	for (auto* key : InGame::keys)
	{
		if (!key)
			return;

		SDK::Key_GrabbedKey(key, nullptr);
		grabbed++;
	}

	char msg[64];
	snprintf(msg, sizeof(msg), "Grabbed %u keys.", grabbed);
	NOTIFY_INFO_QUICK(msg);
}


void GrabKeys::GrabKeysMain()
{
	if (!CONFIG_BOOL(GetConfigManager(), "AutoGrabKeys")) return;

	if (InGame::keys.empty())
		return;

	for (auto* key : InGame::keys)
	{
		if (!key)
			return;

		SDK::Key_GrabbedKey(key, nullptr);
	}
}

#include "alwaysbloodmoon.h"

using namespace PhasmoCheatV::Features::Map;

AlwaysBloodMoon::AlwaysBloodMoon() : FeatureCore(LANG("AlwaysBloodMoon_Header"), TYPE_MISC) {}

void AlwaysBloodMoon::OnMenuRender()
{
	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("AlwaysBloodmoonEnable"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
}
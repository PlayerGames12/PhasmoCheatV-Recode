#include "exitvanone.h"

using namespace PhasmoCheatV::Features::Misc;

ExitVanOne::ExitVanOne() : FeatureCore("Exit Van Solo (host)", TYPE_MISC) {}
void ExitVanOne::OnMenuRender()
{
	bool enabled = IsActive();
	if (ImGui::Checkbox("Leave People", &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
}

bool ExitVanOne::ExitVanOneMain(SDK::ExitLevel* exitLevel, SDK::MethodInfo* methodInfo)
{
	if (!IsActive() || !Utils::IsLocalMasterClient())
		return SDK::ExitLevel_ThereAreAlivePlayersOutsideTheTruck(exitLevel, methodInfo);

	return false;
}

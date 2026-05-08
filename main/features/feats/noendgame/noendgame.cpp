#include "noendgame.h"

using namespace PhasmoCheatV::Features::Misc;

NoEndGame::NoEndGame() : FeatureCore(LANG("NoEndGame_Header"), TYPE_MISC) {}

void NoEndGame::OnMenuRender()
{
	bool enabled = IsActive();

	if (ImGui::Checkbox(LANG("EnableNoEndGame"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
}

void NoEndGame::NoEndGameMain(SDK::GameController* gameController, SDK::Player* player, SDK::MethodInfo* methodInfo)
{
	if (IsActive())
		return;

	SDK::GameController_PlayerDied(gameController, player, methodInfo);
}
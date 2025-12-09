#include "antikick.h"

using namespace PhasmoCheatV::Features::Misc;

AntiKick::AntiKick() : FeatureCore("AntiKick", TYPE_MISC) {}
void AntiKick::OnMenuRender()
{
	bool enabled = IsActive();
	if (ImGui::Checkbox("AntiKick", &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
}

void AntiKick::AntiKickMain(SDK::ServerManager* serverManager, const bool isBanned, void* photonMessageInfo, SDK::MethodInfo* methodInfo)
{
	if (!IsActive() || Utils::IsLocalMasterClient())
		return SDK::ServerManager_KickPlayerNetworked(serverManager, isBanned, photonMessageInfo, methodInfo);

	NOTIFY_INFO_QUICK("The host tried to kick you out!");
}

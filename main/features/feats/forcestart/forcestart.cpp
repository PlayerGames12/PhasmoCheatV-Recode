#include "forcestart.h"

using namespace PhasmoCheatV::Features::Misc;

ForceStart::ForceStart() : FeatureCore("Force Start", TYPE_MISC) {}

void ForceStart::OnActivate()
{
	auto* serverManager = Utils::GetServerManager();
	if (!serverManager) return;
	SourceText = Utils::UnityStrToSysStr(*SDK::TMP_Text_get_text(reinterpret_cast<SDK::TMP_Text*>(serverManager->Fields.readyText), nullptr));
	if (SourceText != "Force start by PhasmoCheatV")
		SDK::TMP_Text_set_text(reinterpret_cast<SDK::TMP_Text*>(serverManager->Fields.readyText), Utils::SysStrToUnityStr("Force start by PhasmoCheatV"), nullptr);
	else
		return;
}

void ForceStart::OnDeactivate()
{
	auto* serverManager = Utils::GetServerManager();
	if (!serverManager) return;
	if (Utils::UnityStrToSysStr(*SDK::TMP_Text_get_text(reinterpret_cast<SDK::TMP_Text*>(serverManager->Fields.readyText), nullptr)) == "Force start by PhasmoCheatV")
		SDK::TMP_Text_set_text(reinterpret_cast<SDK::TMP_Text*>(serverManager->Fields.readyText), Utils::SysStrToUnityStr(SourceText), nullptr);
	else
		return;
}

void ForceStart::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));
	bool enabled = IsActive();
	if (ImGui::Checkbox("Enable Force Start", &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
	ImGui::PopStyleVar();
}

void ForceStart::ForceStartMain(SDK::ServerManager* serverManager)
{
	if (!IsActive()) return;
	SDK::ServerManager_StartGame(serverManager, nullptr);
}
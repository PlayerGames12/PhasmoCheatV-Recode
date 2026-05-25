#include "awesp.h"

using namespace PhasmoCheatV::Features::Visuals;

AWEsp::AWEsp() : FeatureCore("AW ESP", TYPE_VISUALS) {}

void AWEsp::OnRender()
{
	if (!IsActive() || InGame::awDolls.empty()) return;

	for (int i = 0; i < InGame::awDolls.size(); i++)
	{
		auto* awDoll = reinterpret_cast<SDK::Component*>(InGame::awDolls[i]);
		if (!awDoll || (uintptr_t)awDoll < 0x10000)
			continue;

		SDK::Transform* tr_doll = nullptr;

		__try
		{
			tr_doll = SDK::Component_Get_Transform(awDoll, nullptr);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			continue;
		}

		if (!tr_doll) continue;

		const auto worldPos = Utils::GetPosVec3(tr_doll);
		SDK::Vector3 screenPos;

		if (!Utils::WTS(worldPos, screenPos))
			continue;

		const auto draw = ImGui::GetBackgroundDrawList();
		ImFont* normalFont = ImGui::GetFont();
		float normalFontSize = ImGui::GetFontSize();

		draw->AddText(normalFont, normalFontSize, ImVec2(screenPos.X, screenPos.Y), IM_COL32(255, 255, 255, 255), "AWDoll");
	}
}

void AWEsp::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

	bool enabled = IsActive();
	if (ImGui::Checkbox("Enable AW ESP", &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}

	ImGui::PopStyleVar();
}
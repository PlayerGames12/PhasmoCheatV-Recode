#include "fuseesp.h"

using namespace PhasmoCheatV::Features::Visuals;

FuseBoxESP::FuseBoxESP() : FeatureCore("FuseBox ESP", TYPE_VISUALS)
{
	TextBuffer.reserve(INITIAL_BUFFER_SIZE);

	DECLARE_CONFIG(GetConfigManager(), "ShowStatus", bool, true);
	DECLARE_CONFIG(GetConfigManager(), "Color", ImColor, ImColor(1.f, 1.f, 1.f, 1.f));
}

void FuseBoxESP::OnRender()
{
	if (!InGame::fuseBox)
		return;
	const auto& fuseBoxPosition = Utils::GetPosVec3(InGame::fuseBox->Fields.Field8);
	SDK::Vector3 screenPosition;
	if (!Utils::WTS(fuseBoxPosition, screenPosition))
		return;
	ImDrawList* draw = ImGui::GetBackgroundDrawList();
	ImFont* normalFont = ImGui::GetFont();
	ImFont* iconFont = ImGui::GetIO().Fonts->Fonts[6];
	const ImColor color = CONFIG_COLOR(GetConfigManager(), "Color");
	std::string status = "";
	if (CONFIG_BOOL(GetConfigManager(), "ShowStatus"))
		status = InGame::fuseBox->Fields.IsOn ? "ON" : "OFF";
	float fontSize = ImGui::GetFontSize();
	float bracketWidth = normalFont->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, "[").x;
	float iconWidth = iconFont->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, "E").x;
	float rightBracketWidth = normalFont->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, "] ").x;
	std::string leftBracket = "[";
	draw->AddText(normalFont, fontSize, ImVec2(screenPosition.X, screenPosition.Y), color, leftBracket.c_str());
	std::string iconLetter = "E";
	draw->AddText(iconFont, fontSize, ImVec2(screenPosition.X + bracketWidth, screenPosition.Y), color, iconLetter.c_str());
	std::string rightBracket = "] ";
	draw->AddText(normalFont, fontSize, ImVec2(screenPosition.X + bracketWidth + iconWidth, screenPosition.Y), color, rightBracket.c_str());
	if (!status.empty())
		draw->AddText(normalFont, fontSize, ImVec2(screenPosition.X + bracketWidth + iconWidth + rightBracketWidth, screenPosition.Y), color, status.c_str());
}



void FuseBoxESP::OnMenuRender()
{
	constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;
	bool enabled = IsActive();
	ImColor col = CONFIG_COLOR(GetConfigManager(), "Color");
	bool showStatus = CONFIG_BOOL(GetConfigManager(), "ShowStatus");

	if (ImGui::Checkbox("Enable fusebox esp##fuseBoxESP", &enabled)) {
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
	ImGui::SameLine();
	if (enabled)
	{
		if (ImGui::ColorEdit4("Color##fuseBoxESP", reinterpret_cast<float*>(&col.Value), colorEditFlags))
		{
			SET_CONFIG_VALUE(GetConfigManager(), "Color", ImColor, col);
		}
		if (ImGui::Checkbox("Show status##fuseBoxESP", &showStatus))
		{
			SET_CONFIG_VALUE(GetConfigManager(), "ShowStatus", bool, showStatus);
		}
	}
}
#include "jackalopeesp.h"

using namespace PhasmoCheatV::Features::Visuals;

JackalopeESP::JackalopeESP() : FeatureCore(LANG("JackalopeESP_Header"), TYPE_VISUALS) {}

void JackalopeESP::OnRender()
{
    if (!IsActive())
        return;

    if (InGame::jackalope.empty())
        return;

    auto draw = ImGui::GetBackgroundDrawList();
    const ImColor color = ImColor(255, 0, 255, 255);

    for (auto jack : InGame::jackalope)
    {
        if (!jack)
            continue;

        auto* jackalope_gobj = SDK::Component_Get_GameObject(reinterpret_cast<SDK::Component*>(jack), nullptr);
        if (!jackalope_gobj)
            continue;

        bool act = SDK::GameObject_get_activeSelf(jackalope_gobj, nullptr);
        if (!act)
            continue;

        auto transform = SDK::Component_Get_Transform(reinterpret_cast<SDK::Component*>(jack), nullptr);
        if (!transform)
            continue;

        SDK::Vector3 worldPos = Utils::GetPosVec3(transform);
        worldPos.Y += 1.5f;

        SDK::Vector3 screenPos;
        if (!Utils::WTS(worldPos, screenPos) || screenPos.Z <= 0)
            continue;

        const char* name = "Jackalope";
        ImVec2 textSize = ImGui::CalcTextSize(name);

        float x = screenPos.X - textSize.x / 2;
        float y = screenPos.Y;

        draw->AddText(ImVec2(x, y), color, name);

        y += 15;

        float attackChance = jack->Fields.attackChance;
        std::string attackText = "Attack Chance: " + std::to_string((int)attackChance) + "%";
        draw->AddText(ImVec2(x, y), color, attackText.c_str());

        y += 15;

        float runChance = jack->Fields.runAwayChance;
        std::string runText = "Run Chance: " + std::to_string((int)runChance) + "%";
        draw->AddText(ImVec2(x, y), color, runText.c_str());
    }
}

void JackalopeESP::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));
	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("EnableJackalopeESP"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		if (enabled) OnActivate();
		else OnDeactivate();
	}
	ImGui::PopStyleVar();
}
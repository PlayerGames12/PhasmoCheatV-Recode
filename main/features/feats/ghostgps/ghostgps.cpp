#include "ghostgps.h" //todo fix curved lines n much more

using namespace PhasmoCheatV::Features::Visuals;

GhostGPS::GhostGPS() : FeatureCore(LANG("GhostGPS_Header"), TYPE_VISUALS)
{
	DECLARE_CONFIG(GetConfigManager(), "Color", ImColor, ImColor(1.f, 1.f, 1.f, 1.f));
}

void GhostGPS::OnRender()
{
    auto ghostAI = Utils::GetGhostAI();
    if (!ghostAI)
        return;

    auto agent = ghostAI->Fields.NavMeshAgent;
    if (!agent)
        return;

    auto path = SDK::NavMeshAgent_get_path(agent, nullptr);
    if (!path)
        return;

    auto corners = SDK::NavMeshPath_get_corners(path, nullptr);
    if (!corners)
        return;

    auto draw = ImGui::GetBackgroundDrawList();

    for (int32_t i = 0; i < corners->MaxLenght - 1; i++)
    {
        SDK::Vector3 start = corners->Vector[i];
        SDK::Vector3 end = corners->Vector[i + 1];

        SDK::Vector3 screenStart;
        SDK::Vector3 screenEnd;

        if (!Utils::WTS(start, screenStart))
            continue;

        if (!Utils::WTS(end, screenEnd))
            continue;

        draw->AddLine(
                ImVec2(
                    screenStart.X,
                    screenStart.Y
                ),
                ImVec2(
                    screenEnd.X,
                    screenEnd.Y
                ),
                IM_COL32(255, 50, 50, 255),
                3.0f
            );

        draw->AddCircleFilled(
                ImVec2(
                    screenEnd.X,
                    screenEnd.Y
                ),
                5.0f,
                IM_COL32(255, 255, 0, 255)
            );
    }
}

void GhostGPS::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

	bool enabled = IsActive();

	ImColor col = CONFIG_COLOR(GetConfigManager(), "Color");

	if (ImGui::Checkbox(LANG("EnableGhostGPS"), &enabled)) {
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		enabled ? OnActivate() : OnDeactivate();
	}

	ImGui::PopStyleVar();
}
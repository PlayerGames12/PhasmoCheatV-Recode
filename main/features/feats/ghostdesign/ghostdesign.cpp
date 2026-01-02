#include "ghostdesign.h"

using namespace PhasmoCheatV::Features::Ghost;

GhostDesigner::GhostDesigner() : FeatureCore("Ghost Designer (HOST)", TYPE_GHOST)
{
    DECLARE_CONFIG(GetConfigManager(), "GhostAge", int, 0);
    DECLARE_CONFIG(GetConfigManager(), "GhostType", int, static_cast<int>(SDK::GhostType::Spirit));
    DECLARE_CONFIG(GetConfigManager(), "IsShy", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "EvidenceMode", int, 0);
    DECLARE_CONFIG(GetConfigManager(), "EvidenceCount", int, 3);

    for (int i = 0; i < 7; i++) {
        DECLARE_CONFIG(GetConfigManager(), "Evidence" + std::to_string(i), int, i + 1);
    }
}

void GhostDesigner::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox("Enable Ghost Designer", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (!enabled) {
        ImGui::PopStyleVar();
        return;
    }

    int ghostAge = CONFIG_INT(GetConfigManager(), "GhostAge");
    if (ImGui::SliderInt("Ghost Age##ghostDesigner", &ghostAge, -1000, 1000))
        SET_CONFIG_VALUE(GetConfigManager(), "GhostAge", int, ghostAge);

    const char* ghostTypes[] = {
        "Spirit","Wraith","Phantom","Poltergeist","Banshee",
        "Jinn","Mare","Revenant","Shade","Demon",
        "Yurei","Oni","Hantu","Yokai","Goryo",
        "Myling","Onryo","The Twins","Raiju","Obake",
        "Mimic","Moroi","Deogen","Thaye","None",
        "Gallu","Dayan","Obambo"
    };

    int ghostType = CONFIG_INT(GetConfigManager(), "GhostType");
    if (ImGui::Combo("Ghost Type##ghostDesigner", &ghostType, ghostTypes, IM_ARRAYSIZE(ghostTypes)))
        SET_CONFIG_VALUE(GetConfigManager(), "GhostType", int, ghostType);

    bool isShy = CONFIG_BOOL(GetConfigManager(), "IsShy");
    if (ImGui::Checkbox("Is Shy##ghostDesigner", &isShy))
        SET_CONFIG_VALUE(GetConfigManager(), "IsShy", bool, isShy);

    ImGui::Separator();
    ImGui::Text("Evidence Settings");

    const char* evidenceModes[] = { "Random", "Selected" };
    int evidenceMode = CONFIG_INT(GetConfigManager(), "EvidenceMode");
    if (ImGui::Combo("Mode##EvidenceMode", &evidenceMode, evidenceModes, IM_ARRAYSIZE(evidenceModes)))
        SET_CONFIG_VALUE(GetConfigManager(), "EvidenceMode", int, evidenceMode);

    int evidenceCount = CONFIG_INT(GetConfigManager(), "EvidenceCount");
    if (ImGui::SliderInt("Evidence Count##EvidenceCount", &evidenceCount, 0, 7))
        SET_CONFIG_VALUE(GetConfigManager(), "EvidenceCount", int, evidenceCount);

    if (evidenceMode == 1)
    {
        const char* evidenceNames[] = {
            "None", "EMF Level 5", "Spirit Box", "Fingerprints",
            "Ghost Orb", "Ghost Writing", "Freezing Temps", "D.O.T.S"
        };

        for (int i = 0; i < evidenceCount; i++) {
            std::string configKey = "Evidence" + std::to_string(i);
            int evidenceValue = CONFIG_INT(GetConfigManager(), configKey);

            std::string label = "Evidence " + std::to_string(i + 1) + "##select";
            if (ImGui::Combo(label.c_str(), &evidenceValue, evidenceNames, IM_ARRAYSIZE(evidenceNames)))
                SET_CONFIG_VALUE(GetConfigManager(), configKey, int, evidenceValue);
        }
    }

    ImGui::PopStyleVar();
}

void GhostDesigner::ApplyGhostSettings(int& ghostType, int& ghostAge, bool& isShy)
{
    if (!CONFIG_BOOL(GetConfigManager(), "Enabled"))
        return;

    ghostType = CONFIG_INT(GetConfigManager(), "GhostType");
    ghostAge = CONFIG_INT(GetConfigManager(), "GhostAge");
    isShy = CONFIG_BOOL(GetConfigManager(), "IsShy");
}

void GhostDesigner::ApplyGhostEvidence(int* evidence)
{
    if (!evidence)
        return;

    if (!CONFIG_BOOL(GetConfigManager(), "Enabled"))
        return;

    int mode = CONFIG_INT(GetConfigManager(), "EvidenceMode");
    int evidenceCount = CONFIG_INT(GetConfigManager(), "EvidenceCount");

    int count = *(int*)((uintptr_t)evidence + 0x18);
    int* evidenceData = (int*)((uintptr_t)evidence + 0x20);

    std::vector<int> newEvidence;

    if (mode == 0)
    {
        std::vector<int> pool = { 1,2,3,4,5,6,7 };
        std::mt19937 gen(std::random_device{}());
        std::shuffle(pool.begin(), pool.end(), gen);
        evidenceCount = std::clamp(evidenceCount, 0, (int)pool.size());
        newEvidence.assign(pool.begin(), pool.begin() + evidenceCount);
    }
    else
    {
        for (int i = 0; i < evidenceCount; i++)
            newEvidence.push_back(CONFIG_INT(GetConfigManager(), "Evidence" + std::to_string(i)));
    }

    *(int*)((uintptr_t)evidence + 0x18) = (int)newEvidence.size();
    for (size_t i = 0; i < newEvidence.size(); i++)
        evidenceData[i] = newEvidence[i];
}
#include "ghostmodifier.h"

using namespace PhasmoCheatV::Features::Ghost;

const char* ghostStateList[] = {
    "Idle", "Wander", "Hunting", "FavouriteRoom", "Light", "Door", "Throwing", "FuseBox", "Appear", "DoorKnock", "WindowKnock", "CarAlarm", "Flicker", "CCTV", "RandomEvent",
    "GhostAbility", "Mannequin", "TeleportObject", "Interact", "SummoningCircle", "MusicBox", "Dots", "Salt"
};

GhostModifier::GhostModifier() : FeatureCore(LANG("GhostModifier_Header"), TYPE_GHOST)
{
    DECLARE_CONFIG(GetConfigManager(), "CustomSpeedEnabled", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "GhostSpeed", float, 3.f);
    DECLARE_CONFIG(GetConfigManager(), "ForceState", int, static_cast<int>(SDK::GhostState::Idle));
    DECLARE_CONFIG(GetConfigManager(), "ShouldForceAppear", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "ShouldChangeState", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "FreezeState", bool, false);
}

void GhostModifier::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (BCheckBox(LANG("EnableGhostModifier"), &enabled, "b_EnableGhostModifier"))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled)
    {
        bool customSpeedEnabled = CONFIG_BOOL(GetConfigManager(), "CustomSpeedEnabled");
        if (ImGui::Checkbox((std::string(LANG("EnableCustomGhostSpeed")) + "##ghostModifier_customSpeed").c_str(), &customSpeedEnabled))
            SET_CONFIG_VALUE(GetConfigManager(), "CustomSpeedEnabled", bool, customSpeedEnabled);

        float ghostSpeed = CONFIG_FLOAT(GetConfigManager(), "GhostSpeed");
        if (ImGui::SliderFloat((std::string(LANG("GhostSpeedMod")) + "##ghostModifier_speed").c_str(), &ghostSpeed, 0.0f, 15.0f, "%.1f"))
            SET_CONFIG_VALUE(GetConfigManager(), "GhostSpeed", float, ghostSpeed);

        ImGui::Separator();

        if (ImGui::Button((std::string(LANG("ForceAppear")) + "##ghostModifier_forceAppear").c_str()))
        {
            if (InGame::ghostAI == nullptr)
                NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
            else if (!Utils::IsLocalMasterClient())
                NOTIFY_ERROR_QUICK(LANG("NeedMustBeHost"));
            else
                SET_CONFIG_VALUE(GetConfigManager(), "ShouldForceAppear", bool, true);
        }

        int forcedState = CONFIG_INT(GetConfigManager(), "ForceState");
        if (ImGui::Combo((std::string(LANG("ForcedType")) + "##ghostModifier_forceState").c_str(), &forcedState, ghostStateList, IM_ARRAYSIZE(ghostStateList)))
            SET_CONFIG_VALUE(GetConfigManager(), "ForceState", int, forcedState);

        if (ImGui::Button((std::string(LANG("ForceState")) + "##ghostModifier_applyState").c_str()))
        {
            if (!InGame::ghostAI)
                NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
            else if (!Utils::IsLocalMasterClient())
                NOTIFY_ERROR_QUICK(LANG("NeedMustBeHost"));
            else
                SET_CONFIG_VALUE(GetConfigManager(), "ShouldChangeState", bool, true);
        }

        ImGui::Separator();

        bool freezeState = CONFIG_BOOL(GetConfigManager(), "FreezeState");
        if (ImGui::Checkbox((std::string(LANG("FreezeState")) + "##ghostModifier_freeze").c_str(), &freezeState))
        {
            if (!Utils::IsLocalMasterClient())
            {
                NOTIFY_ERROR_QUICK(LANG("NeedMustBeHost"));
                SET_CONFIG_VALUE(GetConfigManager(), "FreezeState", bool, false);
            }
            else
            {
                SET_CONFIG_VALUE(GetConfigManager(), "FreezeState", bool, freezeState);
            }
        }

        if (SDK::GhostAI* ghost = InGame::ghostAI) {
            if (SDK::GhostModel* ghostModel = ghost->Fields.currentModel) {
                bool isVisibleGhost = Utils::IsGhostVisible(ghost);
                if (ImGui::Button(LANG("SetGhostVisible")))
                {
                    SDK::GhostModel_SetVisibility(ghostModel, !isVisibleGhost, nullptr);
                }
            }
        }
    }
    ImGui::PopStyleVar();
}

void GhostModifier::GhostModifierMain()
{
    if (!IsActive() || !Utils::IsLocalMasterClient()) return;

    if (CONFIG_BOOL(GetConfigManager(), "CustomSpeedEnabled"))
    {
        const float ghostSpeed = CONFIG_FLOAT(GetConfigManager(), "GhostSpeed");
        if (InGame::ghostAI != nullptr)
        {
            InGame::ghostAI->Fields.defaultSpeed = ghostSpeed;
            InGame::ghostAI->Fields.saltSpeedMultiplier = ghostSpeed;
            InGame::ghostAI->Fields.incenseSpeedMultiplier = ghostSpeed;
        }
    }

    bool shouldForceAppear = CONFIG_BOOL(GetConfigManager(), "ShouldForceAppear");
    if (shouldForceAppear && InGame::ghostAI != nullptr)
    {
        ForceAppear();
        SET_CONFIG_VALUE(GetConfigManager(), "ShouldForceAppear", bool, false);
    }

    bool shouldChangeState = CONFIG_BOOL(GetConfigManager(), "ShouldChangeState");
    if (shouldChangeState && InGame::ghostAI != nullptr)
    {
        int forcedState = CONFIG_INT(GetConfigManager(), "ForceState");
        ChangeState(static_cast<SDK::GhostState>(forcedState));
        SET_CONFIG_VALUE(GetConfigManager(), "ShouldChangeState", bool, false);
    }

    bool freezeState = CONFIG_BOOL(GetConfigManager(), "FreezeState");
    if (freezeState && InGame::ghostAI != nullptr)
    {
        int forcedState = CONFIG_INT(GetConfigManager(), "ForceState");
        SDK::GhostState currentForcedState = static_cast<SDK::GhostState>(forcedState);

        if (InGame::ghostAI->Fields.currentState != currentForcedState)
        {
            SDK::GhostAI_ChangeState(InGame::ghostAI, currentForcedState, nullptr, nullptr, nullptr);
        }
    }
}

void GhostModifier::ChangeState(SDK::GhostState forcedState)
{
    if (!IsActive() || !InGame::ghostAI) return;
    SDK::GhostAI_ChangeState(InGame::ghostAI, forcedState, nullptr, nullptr, nullptr);
}

void GhostModifier::ForceAppear()
{
    if (!IsActive() || !InGame::ghostAI) return;
    SDK::GhostAI_Appear(InGame::ghostAI, INT_MAX, nullptr);
}
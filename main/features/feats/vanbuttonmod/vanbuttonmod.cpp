#include "vanbuttonmod.h"

using namespace PhasmoCheatV::Features::Map;

VanButtonModifier::VanButtonModifier() : FeatureCore(LANG("VanButtonModifier_Header"), TYPE_MAP)
{
    DECLARE_CONFIG(GetConfigManager(), "SkipVanAnim", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "AutoOpenVanDoor", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "SkipVanButtonDelay", bool, false);
}

void VanButtonModifier::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox(LANG("VanButtonModifierEnable"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (!enabled)
    {
        ImGui::PopStyleVar();
        return;
    }

	bool skipAnim = CONFIG_BOOL(GetConfigManager(), "SkipVanAnim");
	bool autoOpenDoor = CONFIG_BOOL(GetConfigManager(), "AutoOpenVanDoor");
	bool skipDelay = CONFIG_BOOL(GetConfigManager(), "SkipVanButtonDelay");

	if (ImGui::Checkbox(LANG("SkipVanAnim"), &skipAnim))
        SET_CONFIG_VALUE(GetConfigManager(), "SkipVanAnim", bool, skipAnim);
	if (ImGui::Checkbox(LANG("AutoOpenVan"), &autoOpenDoor))
        SET_CONFIG_VALUE(GetConfigManager(), "AutoOpenVanDoor", bool, autoOpenDoor);
	if (ImGui::Checkbox(LANG("SkipVanButtonDelay"), &skipDelay))
        SET_CONFIG_VALUE(GetConfigManager(), "SkipVanButtonDelay", bool, skipDelay);

    ImGui::PopStyleVar();
}

void VanButtonModifier::VanButtonModifierMain(SDK::LiftButton* liftButton, void* photon, SDK::MethodInfo* methodInfo)
{
    auto* animator = liftButton->Fields.anim;

    if (IsActive())
    {
        if (animator && CONFIG_BOOL(GetConfigManager(), "SkipVanAnim"))
            SDK::Animator_Set_Speed(animator, FLT_MAX, nullptr);
    }
    else
    {
        if (animator)
            SDK::Animator_Set_Speed(animator, 1.f, nullptr);
        else
            LOG_ERROR("Animator is nullptr!");

        if (SDK::Call_WaitForSeconds_is_replaced)
            SDK::Call_WaitForSeconds_restore();
    }

    SDK::LiftButton_AttemptUse(liftButton, photon, methodInfo);

    if (IsActive())
    {
        if (!SDK::Call_WaitForSeconds_is_replaced && CONFIG_BOOL(GetConfigManager(), "SkipVanButtonDelay"))
            SDK::Call_WaitForSeconds_nop(5);

        if (CONFIG_BOOL(GetConfigManager(), "SkipVanButtonDelay"))
        {
            liftButton->Fields.hasUsed = 0;
            liftButton->Fields.timer = 0.f;
            liftButton->Fields.isAnimation = false;

            auto* exitLevel = liftButton->Fields.exitLevel;
            auto* comp = (SDK::Component*)(exitLevel->Fields.invisibleWall);
            auto* go = SDK::Component_Get_GameObject(comp, nullptr);
            bool active = SDK::GameObject_get_activeSelf(go, nullptr);
            if (active)
                SDK::GameObject_SetActive(go, false, nullptr);
        }
    }
}

void VanButtonModifier::AutoOpenVanDoor(SDK::LiftButton* liftButton)
{
    if (InGame::LiftButtonOpenedByCheat || !CONFIG_BOOL(GetConfigManager(), "AutoOpenVanDoor"))
        return;

    if (!liftButton || !liftButton->Fields.view || !InGame::ghostAI)
        return;

    static bool timerStarted = false;
    static float startTime = 0.0f;
    static int rpcCalls = 0;

    float time = SDK::Time_Get_Time(nullptr);

    if (!timerStarted)
    {
        startTime = time;
        timerStarted = true;
        return;
    }

    if (time - startTime < 5.0f)
        return;

    if (rpcCalls >= 2)
        return;

    static auto* attemptUse = Utils::SysStrToUnityStr("AttemptUse");

    SDK::PhotonView_RPC(
        liftButton->Fields.view,
        attemptUse,
        SDK::RpcTarget::All,
        nullptr,
        nullptr
    );

    rpcCalls++;

    if (rpcCalls >= 2)
        InGame::LiftButtonOpenedByCheat = true;
}
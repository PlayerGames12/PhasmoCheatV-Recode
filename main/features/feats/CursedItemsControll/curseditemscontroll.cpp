#include "curseditemscontroll.h"

using namespace PhasmoCheatV::Features::Cursed;

CursedItemsControll::CursedItemsControll() : FeatureCore(LANG("CursedItemsControll_Header"), TYPE_CURSED)
{
    DECLARE_CONFIG(GetConfigManager(), "CardTypeForced", int, static_cast<int>(SDK::TarotCardType::Fool));
    DECLARE_CONFIG(GetConfigManager(), "CardForce", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "InfCards", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "HeartPinDisable", bool, false);
}

void CursedItemsControll::OnMenuRender()
{
    bool musicBoxExists = SDK::CursedItemsController_sFields->instance && SDK::CursedItemsController_sFields->instance->Fields.MusicBox;

    if (musicBoxExists)
    {
        auto* go_mb = SDK::Component_Get_GameObject(reinterpret_cast<SDK::Component*>(SDK::CursedItemsController_sFields->instance->Fields.MusicBox), nullptr);
        SDK::PhotonView* pv_mb = nullptr;

        if (go_mb)
        {
            auto pv_type = SDK::System_Type_GetType(Utils::SysStrToUnityStr("Photon.Pun.PhotonView"), nullptr);
            if (pv_type)
                pv_mb = reinterpret_cast<SDK::PhotonView*>(SDK::GameObject_GetComponent(go_mb, pv_type, nullptr));
        }

        if (ImGui::Button(LANG("UseMusicBox")))
        {
            if (pv_mb)
                SDK::PhotonView_RequestOwnership(pv_mb, nullptr);

            if (Utils::Checks_IsRealSender(SDK::PhotonNetwork_Get_LocalPlayer(nullptr), pv_mb))
            {
                bool isOn = true;

                auto boolClass = il2cpp_get_class("mscorlib", "System", "Boolean");
                if (!boolClass) return;

                void* boxedBool = il2cpp_value_box(boolClass, &isOn);
                if (!boxedBool) return;

                std::vector<void*> params;
                params.push_back(boxedBool);

                auto parameters = Utils::VectorToIl2CppArray<void*>(params, "mscorlib", "System", "Object");
                if (!parameters) return;

                SDK::PhotonView_RPC(pv_mb, Utils::SysStrToUnityStr("UseNetworked"), SDK::RpcTarget::All, parameters, nullptr);
            }
        }

        ImGui::SameLine();

        bool offlineMode = SDK::PhotonNetwork_Get_OfflineMode(nullptr);
        ImGui::BeginDisabled(!offlineMode);
        if (ImGui::Button(LANG("FixMusicBox"))) // Thanks Evelien
        {
            SDK::CursedItem* ci_mb = (SDK::CursedItem*)SDK::CursedItemsController_sFields->instance->Fields.MusicBox;
            ci_mb->Fields.HasBreak = false;
            ci_mb->Fields.InUse = false;
        }
        ImGui::EndDisabled();
    }

    bool isSummoningCircleActive = Utils::IsLocalMasterClient() && SDK::CursedItemsController_sFields->instance && SDK::CursedItemsController_sFields->instance->Fields.SummoningCircle;

    ImGui::BeginDisabled(!isSummoningCircleActive);

    if (ImGui::Button(LANG("StartRitual")))
        needRitualStart = true;

    ImGui::EndDisabled();

    bool heartPinDisabled = CONFIG_BOOL(GetConfigManager(), "HeartPinDisable");
    if (ImGui::Checkbox(LANG("DisableHeartPin"), &heartPinDisabled))
        SET_CONFIG_VALUE(GetConfigManager(), "HeartPinDisable", bool, heartPinDisabled);

    bool enabled = IsActive();
    if (BCheckBox(LANG("TarotCardsModEnable"), &enabled, "b_TarotCardsModEnable"))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled)
    {
        bool forceCards = CONFIG_BOOL(GetConfigManager(), "CardForce");
        if (ImGui::Checkbox(LANG("ForceTarotCards"), &forceCards))
            SET_CONFIG_VALUE(GetConfigManager(), "CardForce", bool, forceCards);

        if (forceCards)
        {
            const char* tarotCardList[] = { "Fool", "Wheel Of Fortune", "Tower", "Devil", "Death", "Hermit", "Moon", "Sun", "High Priestess", "Hanged Man" };
            int currentType = CONFIG_INT(GetConfigManager(), "CardTypeForced");
            if (ImGui::Combo(LANG("CardType"), &currentType, tarotCardList, IM_ARRAYSIZE(tarotCardList)))
                SET_CONFIG_VALUE(GetConfigManager(), "CardTypeForced", int, static_cast<int>(currentType));
        }

        bool infCards = CONFIG_BOOL(GetConfigManager(), "InfCards");
        if (ImGui::Checkbox(LANG("InfTarotCards"), &infCards))
            SET_CONFIG_VALUE(GetConfigManager(), "InfCards", bool, infCards);
    }
}

void CursedItemsControll::TarotCardApplySettings(SDK::TarotCardType& type)
{
    if (!IsActive() || !CONFIG_BOOL(GetConfigManager(), "CardForce"))
        return;

    type = static_cast<SDK::TarotCardType>(CONFIG_INT(GetConfigManager(), "CardTypeForced"));
}

// thx VCom Team and ViniLog❤️
bool CursedItemsControll::TarotCardInfCards(SDK::PhotonView* photonView) // called in PhotonRPC
{
    if (!IsActive())
        return false;

    if (!CONFIG_BOOL(GetConfigManager(), "InfCards"))
        return false;

    if (!photonView) {
        LOG_ERROR("photonView is null");
        return false;
    }

    auto gobj_tcs = SDK::Component_Get_GameObject(reinterpret_cast<SDK::Component*>(photonView), nullptr);
    if (!gobj_tcs) {
        LOG_ERROR("failed to get GameObject from photonView");
        return false;
    }

    auto tarotCards = reinterpret_cast<SDK::TarotCards*>(SDK::GameObject_GetComponentByName(gobj_tcs, Utils::SysStrToUnityStr("TarotCards"), nullptr));
    if (!tarotCards) {
        LOG_ERROR("tarotCards component not found");
        return false;
    }

    auto tarotCard = tarotCards->Fields.tarotCard;
    if (!tarotCard) {
        LOG_ERROR("tarotCard field is null");
        return false;
    }

    auto gobj_tc = SDK::Component_Get_GameObject(reinterpret_cast<SDK::Component*>(tarotCard), nullptr);
    if (!gobj_tc) {
        LOG_ERROR("failed to get GameObject from tarotCard");
        return false;
    }

    auto name = SDK::Object_Get_Name(reinterpret_cast<SDK::Object*>(gobj_tc), nullptr);
    LOG_INFO(Utils::UnityStrToSysStr(*name));

    auto renderer = reinterpret_cast<SDK::Render*>(
        SDK::GameObject_GetComponentByName(gobj_tc, Utils::SysStrToUnityStr("MeshRenderer"), nullptr)
        );
    if (!renderer) {
        LOG_ERROR("renderer component not found");
        return false;
    }

    SDK::Render_set_enabled(renderer, true, nullptr); // show tarot card
    return true; // need for ret
}

void CursedItemsControll::CursedItemsControllMain()
{
    if (pendingTarotReset && std::chrono::steady_clock::now() >= tarotResetAt)
    {
        pendingTarotReset = false;

        auto* resetFunc = SDK::Get_TarotCards_ResetCardDraw();
        if (resetFunc && InGame::tarotCards)
        {
            resetFunc(InGame::tarotCards, nullptr);
        }
    }

    if (!needRitualStart || !SDK::CursedItemsController_sFields->instance)
        return;

    needRitualStart = false;

    auto* sc = SDK::CursedItemsController_sFields->instance->Fields.SummoningCircle;
    if (!sc)
    {
        NOTIFY_ERROR_QUICK(LANG("SummoningCircleNotFound"));
        return;
    }

    auto* localPlayer = Utils::GetLocalPlayer();
    if (!localPlayer)
    {
        NOTIFY_ERROR_QUICK(LANG("LocalPlayerNotFound"));
        return;
    }

    auto* func_beginRitual = SDK::Get_SummoningCircle_BeginRitual();
    if (func_beginRitual)
    {
        func_beginRitual(sc, 0);
        NOTIFY_SUCCESS_QUICK(LANG("RitualStarted"));
    }
}

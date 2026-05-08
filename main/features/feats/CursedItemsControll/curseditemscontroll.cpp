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
    bool musicBoxExists = InGame::cursedItemsController && InGame::cursedItemsController->Fields.MusicBox;

    if (musicBoxExists)
    {
        auto* go_mb = SDK::Component_Get_GameObject(reinterpret_cast<SDK::Component*>(InGame::cursedItemsController->Fields.MusicBox), 0);
        SDK::PhotonView* pv_mb = nullptr;

        if (go_mb)
        {
            auto pv_type = SDK::System_Type_GetType(Utils::SysStrToUnityStr("Photon.Pun.PhotonView"), 0);
            if (pv_type)
                pv_mb = reinterpret_cast<SDK::PhotonView*>(SDK::GameObject_GetComponent(go_mb, pv_type, 0));
        }

        if (ImGui::Button(LANG("UseMusicBox")))
        {
            if (pv_mb)
                SDK::PhotonView_RequestOwnership(pv_mb, 0);

            if (Utils::Checks_IsRealSender(SDK::PhotonNetwork_Get_LocalPlayer(0), pv_mb))
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

                SDK::PhotonView_RPC(pv_mb, Utils::SysStrToUnityStr("UseNetworked"), SDK::RpcTarget::All, parameters, 0);
            }
        }

        ImGui::SameLine();

        bool offlineMode = SDK::PhotonNetwork_Get_OfflineMode(0);
        ImGui::BeginDisabled(!offlineMode);
        if (ImGui::Button(LANG("FixMusicBox"))) // Thanks Evelien
        {
            SDK::CursedItem* ci_mb = (SDK::CursedItem*)InGame::cursedItemsController->Fields.MusicBox;
            ci_mb->Fields.HasBreak = false;
            ci_mb->Fields.InUse = false;
        }
        ImGui::EndDisabled();
    }

    bool isSummoningCircleActive = Utils::IsLocalMasterClient() && InGame::cursedItemsController && InGame::cursedItemsController->Fields.SummoningCircle;

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

// Tanks VCom Team and ViniLog❤️
void CursedItemsControll::TarotCardInfCards(SDK::TarotCards* tarotCards, SDK::MethodInfo* methodInfo)
{
    auto& original = SDK::Get_TarotCards_GrabCard_All();
    original[0](tarotCards, methodInfo);

    if (!IsActive() || !CONFIG_BOOL(GetConfigManager(), "InfCards"))
        return;

    InGame::tarotCards = tarotCards;
    pendingTarotReset = true;
    tarotResetAt = std::chrono::steady_clock::now() + std::chrono::milliseconds(2800);
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

    if (!needRitualStart || !InGame::cursedItemsController)
        return;

    needRitualStart = false;

    auto* sc = InGame::cursedItemsController->Fields.SummoningCircle;
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

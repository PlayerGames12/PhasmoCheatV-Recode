#include "curseditemscontroll.h"

using namespace PhasmoCheatV::Features::Cursed;

CursedItemsControll::CursedItemsControll() : FeatureCore("CursedItems Controll", TYPE_CURSED)
{
    DECLARE_CONFIG(GetConfigManager(), "CardTypeForced", int, static_cast<int>(SDK::TarotCardType::Fool));
    DECLARE_CONFIG(GetConfigManager(), "CardForce", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "InfCards", bool, false);
}

void CursedItemsControll::OnMenuRender()
{
    if (ImGui::Button("Break cursed items##cursed"))
    {
        if (InGame::cursedItemsController == nullptr)
            return NOTIFY_ERROR_QUICK("You need to be in the game.");

        if (!Utils::IsLocalMasterClient())
            return NOTIFY_ERROR_QUICK("You must be the host to use this feature.");

        if (InGame::cursedItemsController->Fields.OuijaBoard)
            SDK::CursedItem_BreakItem(reinterpret_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.OuijaBoard), nullptr);

        if (InGame::cursedItemsController->Fields.MusicBox)
            SDK::CursedItem_BreakItem(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.MusicBox), nullptr);

        if (InGame::cursedItemsController->Fields.TarotCards)
            SDK::CursedItem_BreakItem(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.TarotCards), nullptr);

        if (InGame::cursedItemsController->Fields.SummoningCircle)
            SDK::CursedItem_BreakItem(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.SummoningCircle), nullptr);

        if (InGame::cursedItemsController->Fields.HauntedMirror)
            SDK::CursedItem_BreakItem(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.HauntedMirror), nullptr);

        if (InGame::cursedItemsController->Fields.VoodooDoll)
            SDK::CursedItem_BreakItem(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.VoodooDoll), nullptr);

        if (InGame::cursedItemsController->Fields.MonkeyPaw)
            SDK::CursedItem_BreakItem(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.MonkeyPaw), nullptr);
    }

    if (ImGui::Button("Use cursed items##cursed"))
    {
        if (InGame::cursedItemsController == nullptr)
            return NOTIFY_ERROR_QUICK("You need to be in the game.");

        if (InGame::cursedItemsController->Fields.OuijaBoard)
            SDK::CursedItem_Use(reinterpret_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.OuijaBoard), nullptr);

        if (InGame::cursedItemsController->Fields.MusicBox)
            SDK::CursedItem_Use(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.MusicBox), nullptr);

        if (InGame::cursedItemsController->Fields.TarotCards)
            SDK::CursedItem_Use(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.TarotCards), nullptr);

        if (InGame::cursedItemsController->Fields.HauntedMirror)
            SDK::CursedItem_Use(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.HauntedMirror), nullptr);
    }

    bool enabled = IsActive();

    if (ImGui::Checkbox("Active tarot cards modifier##cursed", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }


    if (enabled)
    {
        bool forceCards = CONFIG_BOOL(GetConfigManager(), "CardForce");
        if (ImGui::Checkbox("Force Card Type##cursed", &forceCards))
            SET_CONFIG_VALUE(GetConfigManager(), "CardForce", bool, forceCards);

        if (forceCards)
        {
            const char* tarotCardList[] = { "Fool", "Wheel Of Fortune", "Tower", "Devil", "Death", "Hermit", "Moon", "Sun", "High Priestess", "Hanged Man" };
            int currentType = CONFIG_INT(GetConfigManager(), "CardTypeForced");
            if (ImGui::Combo("Card Type##cursed", &currentType, tarotCardList, IM_ARRAYSIZE(tarotCardList)))
                SET_CONFIG_VALUE(GetConfigManager(), "CardTypeForced", int, static_cast<int>(currentType));
        }

        bool infCards = CONFIG_BOOL(GetConfigManager(), "InfCards");
        if (ImGui::Checkbox("Infinite cards##cursed", &infCards))
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
    if (!IsActive() || !CONFIG_BOOL(GetConfigManager(), "InfCards"))
    {
        auto& original = SDK::Get_TarotCards_GrabCard_All();
        original[0](tarotCards, methodInfo);
    }

    std::thread([tarotCards]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(2800));

            auto* resetFunc = SDK::Get_TarotCards_ResetCardDraw();
            if (resetFunc && tarotCards)
            {
                resetFunc(tarotCards, nullptr);
            }

        }).detach();
}
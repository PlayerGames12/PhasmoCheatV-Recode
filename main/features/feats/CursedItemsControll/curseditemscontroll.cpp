#include "curseditemscontroll.h"

using namespace PhasmoCheatV::Features::Cursed;

CursedItemsControll::CursedItemsControll() : FeatureCore("CursedItems Controll", TYPE_CURSED)
{
    DECLARE_CONFIG(GetConfigManager(), "CardTypeForced", int, static_cast<int>(SDK::TarotCardType::Fool));
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
            SDK::CursedItem_BreakItem(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.OuijaBoard), nullptr);

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
            SDK::CursedItem_Use(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.OuijaBoard), nullptr);

        if (InGame::cursedItemsController->Fields.MusicBox)
            SDK::CursedItem_Use(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.MusicBox), nullptr);

        if (InGame::cursedItemsController->Fields.TarotCards)
            SDK::CursedItem_Use(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.TarotCards), nullptr);

        if (InGame::cursedItemsController->Fields.HauntedMirror)
            SDK::CursedItem_Use(static_cast<SDK::CursedItem*>(InGame::cursedItemsController->Fields.HauntedMirror), nullptr);
    }

    bool enabled = IsActive();
    if (ImGui::Checkbox("Force Card Type##cursed", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled)
    {
        const char* tarotCardList[] = { "Fool", "Wheel Of Fortune", "Tower", "Devil", "Death", "Hermit", "Moon", "Sun", "High Priestess", "Hanged Man" };
        int currentType = CONFIG_INT(GetConfigManager(), "CardTypeForced");
        if (ImGui::Combo("Card Type##cursed", &currentType, tarotCardList, IM_ARRAYSIZE(tarotCardList)))
            SET_CONFIG_VALUE(GetConfigManager(), "CardTypeForced", int, static_cast<int>(currentType));
    }
}

void CursedItemsControll::TarotCardApplySettings(SDK::TarotCardType& type)
{
    if (!IsActive())
        return;

    type = static_cast<SDK::TarotCardType>(CONFIG_INT(GetConfigManager(), "CardTypeForced"));
}
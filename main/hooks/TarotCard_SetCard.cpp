#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkTarotCard_SetCard(SDK::TarotCard* tarotCard, SDK::TarotCardType type, SDK::MethodInfo* methodInfo)
{
    LOG_CALL("Called TarotCard_SetCard");

    CALL_METHOD_IF_ACTIVE_ARGS(Cursed, CursedItemsControll, TarotCardApplySettings, type);

    auto* cards = tarotCard->Fields.cards;
    if (cards)
    {
        InGame::tarotCards = cards;

        bool hasBroken = cards->Fields.hasBroken;
        bool hasInitialized = cards->Fields.hasInitialised;

        cards->Fields.hasBroken = 0;

        LOG_DEBUG("has broken = ", hasBroken);
        LOG_DEBUG("has initialized = ", hasInitialized);

    }
    else
    {
        LOG_ERROR("!Cards, address", cards);
    }
    

    SDK::TarotCard_SetCard(tarotCard, type, methodInfo);
}
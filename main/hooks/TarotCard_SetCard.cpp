#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkTarotCard_SetCard(SDK::TarotCard* instance, SDK::TarotCardType type, SDK::MethodInfo* methodInfo)
{
    LOG_CALL("Called TarotCard_SetCard");

    CALL_METHOD_IF_ACTIVE_ARGS(Cursed, CursedItemsControll, TarotCardApplySettings, type);

    SDK::TarotCard_SetCard(instance, type, methodInfo);
}
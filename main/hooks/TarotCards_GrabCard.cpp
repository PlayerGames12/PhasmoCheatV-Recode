#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkTarotCards_GrabCard(SDK::TarotCards* tarotCards, SDK::MethodInfo* methodInfo)
{
    LOG_CALL("hkTarotCards_GrabCard called");

    CALL_METHOD_ARGS(Cursed, CursedItemsControll, TarotCardInfCards, tarotCards, methodInfo);
}
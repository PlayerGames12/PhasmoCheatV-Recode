#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkTarotCards_BreakItem(SDK::TarotCards* tarotCards, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called TarotCards_BreakItem");

	SDK::TarotCards_BreakItem(tarotCards, methodInfo);
}
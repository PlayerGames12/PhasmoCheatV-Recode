#pragma once
#include "sdk.h"

namespace SDK
{
	struct TarotCard;

	DEC_MET(TarotCard_SetCard, void(*)(TarotCard* tarotCard, TarotCardType type, MethodInfo* methodInfo), "Assembly-CSharp", "", "TarotCard", "SetCard", 1);
}

#pragma once
#include "sdk.h"

namespace SDK
{
	struct TarotCardFields
	{
		MonoBehaviourPunFields monoBehaviourPunFields;
		TarotCards* cards;
	};

	struct TarotCard
	{
		void* Clazz;
		void* Monitor;
		TarotCardFields Fields;
	};

	DEC_MET(TarotCard_SetCard, void(*)(TarotCard* tarotCard, TarotCardType type, MethodInfo* methodInfo), "Assembly-CSharp", "", "TarotCard", "SetCard", 1);
}

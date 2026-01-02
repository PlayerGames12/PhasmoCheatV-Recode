  #pragma once
#include "sdk.h"

namespace SDK
{
	struct TarotCardsFields
	{
		char pad_000[0x1A8];
		bool inUse; // It is worked. Please don't change
		bool hasBroken; // It is worked. Please don't change
		bool hasInitialised; // It is worked. Please don't change
	};

	struct TarotCards
	{
		void* Clazz;
		void* Monitor;
		TarotCardsFields Fields;
	};

	enum class TarotCardType : int32_t
	{
		Fool,
		WheelOfFortune,
		Tower,
		Devil,
		Death,
		Hermit,
		Moon,
		Sun,
		HighPriestess,
		HangedMan
	};

	// SIGNATURE TarotCards_CanUse: 40 53 48 83 EC ? 80 3D ? ? ? ? 00 48 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 33 D2 48 8B CB E8 ? ? ? ? 84 C0 74 ? 48 8B 83.
	// Don't use this signature for Infinite TarotCards as it is useless and will break the game.
	DECLARE_PATTERN_POINTER_MORE(TarotCards_GrabCard, void(*)(TarotCards* tarotCards, MethodInfo* methodInfo), L"GameAssembly.dll", "il2cpp", "40 53 48 83 EC ? 80 3D ? ? ? ? 00 48 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 8B ? ? ? ? 48 89 7C 24", 20);
	DECLARE_PATTERN_POINTER(TarotCards_ResetCardDraw, void(*)(TarotCards* tarotCards, MethodInfo* methodInfo), L"GameAssembly.dll", "il2cpp", "40 53 48 83 EC ? 48 8B 41 ? 48 8B D9 C6 81 ? ? ? ? 00 48 85 C0 74 ? 48 8B 40 ? 48 85 C0 74 ? 80 78 ? 00 74 ? 33 C9 E8 ? ? ? ? 84 C0 74 ? 48 8B 43 ? 48 85 C0 74 ? C6 40 ? ? 48 83 C4 ? 5B C3 33 C9 E8 ? ? ? ? 48 85 C0 74 ? 48 8B 40 ? 48 85 C0 74 ? 48 8B 80 ? ? ? ? 48 85 C0 74 ? C6 80 ? ? ? ? 00 48 83 C4 ? 5B C3 E8 ? ? ? ? ? ? ? ? ? ? ? 48 89 5C 24");
	DEC_MET(TarotCards_BreakItem, void(*)(TarotCards* tarotCards, MethodInfo* methodInfo), "Assembly-CSharp", "", "TarotCards", "BreakItem", 0);
}

#pragma once
#include "sdk.h"

namespace SDK
{
	enum class CursedItemType : int32_t
	{
		None,
		TarotCards,
		OuijaBoard,
		HauntedMirror,
		MusicBox,
		SummoningCircle,
		VoodooDoll,
		MonkeyPaw
	};

	struct CursedItemEnumArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds;
		void* MaxLength;
		CursedItemType Vector[65535];
	};

	struct __declspec(align(8)) ListCursedItemEnumFields
	{
		CursedItemEnumArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot;
	};

	struct ListCursedItemEnum
	{
		void* Clazz;
		void* Monitor;
		ListCursedItemEnumFields Fields;
	};

	struct CursedItemsControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* OuijaBoard;
		void* MusicBox;
		void* TarotCards;
		void* SummoningCircle;
		void* HauntedMirror;
		void* VoodooDoll;
		void* MonkeyPaw;
		void* OuijaBoardSpawnSpots;
		void* MusicBoxSpawnSpots;
		void* TarotCardsSpawnSpots;
		void* SummoningCircleSpawnSpots;
		void* HauntedMirrorSpawnSpots;
		void* VoodooDollSpawnSpots;
		void* MonkeyPawSpawnSpots;
		ListCursedItemEnum* CursedItems;
	};

	struct CursedItemsController
	{
		void* Clazz;
		void* Monitor;
		CursedItemsControllerFields Fields;
	};

	DEC_MET(CursedItemsController_Awake, void(*)(CursedItemsController* cursedItemsController, MethodInfo* methodInfo), "Assembly-CSharp", "", "cursedItemsController", "Awake", 0);
}
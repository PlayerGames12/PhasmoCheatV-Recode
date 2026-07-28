#pragma once
#include "sdk.h"

namespace SDK
{
	struct Crucifix;

	struct CrucifixArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds;
		uint32_t MaxLength;
		Crucifix* Vector[1];
	};

	struct CrucifixListFields
	{
		CrucifixArray* _items;
		int32_t _size;
		int32_t _version;
		void* _syncRoot;
	};

	struct CrucifixList
	{
		void* Clazz;
		void* Monitor;
		CrucifixListFields Fields;
	};

	struct LevelControllerFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		void* smallMapVariations;
		LevelRoom* currentPlayerRoom;
		LevelRoom* currentGhostRoom;
		GhostAI* ghostAI;
		DoorArray* doors;
		void* allGhostRooms;
		void* allInteriorRooms;
		void* fuseboxSpawnLocations;
		void* MannequinTeleportSpots;
		LevelRoom* outsideRoom;
		bool isOutsideMap;
		char pad_000[0x7];
		FuseBox* fuseBox;
		GameController* gameController;
		void* soundController;
		void* itemSpawner;
		void* cursedController;
		DoorArray* exitDoors;
		void* levelAreas;
		CrucifixList* crucifix;
		void* fireSources;
		void* allEquipment;
		void* possibleMaleFirstNames;
		void* possibleFemaleFirstNames;
		void* possibleLastNames;
		void* mainDoorKey;
		void* allBlockedZones;
		int32_t intermediateZonesBlocked;
		int32_t proZonesBlocked;
		int32_t nightmareZonesBlocked;
		char pad_001[0x4];
		void* allClothDoors;
		void* fps;
		bool Field100;
		char pad_002[0x7];
	};

	struct LevelController
	{
		void* Clazz;
		void* Monitor;
		LevelControllerFields Fields;
	};

	struct LevelController_staticFields
	{
		LevelController* instance;
	};
	
	DEC_MET(LevelController_Start, void(*)(LevelController* levelController, MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelController", "Start", 0);
	DEC_SFIELD(LevelController_sFields, LevelController_staticFields, "Assembly-CSharp", "", "LevelController");
}

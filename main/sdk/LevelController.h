#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelControllerFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		void* smallMapVariations;
		LevelRoom* currentPlayerRoom;
		LevelRoom* currentGhostRoom;
		GhostAI* ghostAI;
		DoorArray* doors;
		void* Field5;
		void* Field6;
		void* Field7;
		void* Field8;
		LevelRoom* Field9;
		bool Field10;
		FuseBox* fuseBox;
		GameController* GameController;
		void* Field14;
		void* Field15;
		DoorArray* exitDoors;
		void* Field17;
		void* Field18;
		void* Field19;
		void* PhotonObjectInteractList;
		void* Field20;
		void* Field21;
		void* Field22;
		void* Field23;
		void* Field24;
		int Field25;
		int Field26;
		int Field27;
		void* Field29;
		void* Field30;
	};

	struct LevelController
	{
		void* Clazz;
		void* Monitor;
		LevelControllerFields Fields;
	};
	
	DEC_MET(LevelController_Start, void(*)(LevelController* levelController, MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelController", "Start", 0);
}

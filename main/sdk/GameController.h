#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelController;

	struct GameControllerFields
	{
		MonoBehaviourPunCallbacksFields MonoBehaviourPunCallbacksFields;
		void* Field0;
		void* Field01;
		void* Field1;
		void* Field2;
		void* Field3;
		void* Field31;
		void* Field32;
		void* Field4;
		void* Field5;
		void* Field51;
		void* Field6;
		void* Field7;
		void* Field8;
		void* Field9;
		void* Field10;
		void* Field101;
		float Field11;
		void* Field12;
		LevelController* LevelController;
		void* Field14;
		bool Field15;
		int Field16;
		void* Field17;
		bool Field18;
		void* Field19;
	};

	struct GameController
	{
		void* Clazz;
		void* Monitor;
		GameControllerFields Fields;
	};

	DEC_MET(GameController_Exit, void(*)(GameController* gameController, void* photoMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "GameController", "Exit", 1);
	DEC_MET(GameController_GetAveragePlayerInsanity, float(*)(GameController* gameController, MethodInfo* methodInfo), "Assembly-CSharp", "", "GameController", "GetAveragePlayerInsanity", 0);
}

#pragma once
#include "sdk.h"

namespace SDK
{
	struct MapControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* PlayerIcons;
		ListPlayer* Players;
		void* AllFloors;
		int32_t Index;
		float IconScale;
		float PlayerIconScale;
		void* MotionSensorData;
		GameController* GameController;
		void* DefaultFloor;
		Vector3 PlayerIconOffset;
		Camera* MapCamera;
	};

	struct MapController
	{
		void* Clazz;
		void* Monitor;
		MapControllerFields Fields;
	};


	DEC_MET(MapController_Start, void(*)(MapController* mapController, MethodInfo* methodInfo), "Assembly-CSharp", "", "MapController", "Start", 0);
}

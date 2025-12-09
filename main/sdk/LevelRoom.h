#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelRoomFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* Field1;
		void* Field2;
		void* RoomColliders;
		Transform* Field4;
		void* AudioReverbZone;
		int32_t Field5;
		void* Field7;
		int32_t Field6;
		String* RoomName;
		float temperature;
	};

	struct LevelRoom
	{
		void* Clazz;
		void* Monitor;
		LevelRoomFields Fields;
	};
}

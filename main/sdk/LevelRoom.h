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
		void* roomCollidersToIgnoreForWander;
		Transform* Field4;
		void* AudioReverbZone;
		void* Field40;
		int32_t Field5;
		char pad_000[0x4];
		void* Field7;
		int32_t Field6;
		char pad_001[0x4];
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

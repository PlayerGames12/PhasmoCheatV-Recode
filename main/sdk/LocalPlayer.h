#pragma once
#include "sdk.h"

namespace SDK
{
	struct Player;

	struct LocalPlayerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		Player* Player;
		void* journalController;
		Camera* Camera;
	};

	struct LocalPlayer
	{
		void* Clazz;
		void* Monitor;
		LocalPlayerFields Fields;
	};

	DEC_MET(LocalPlayer_TeleportPlayer, void(*)(LocalPlayer* player, Vector3 position, MethodInfo* methodInfo), "Assembly-CSharp", "", "LocalPlayer", "TeleportPlayer", 1);
}
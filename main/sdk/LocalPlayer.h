#pragma once
#include "sdk.h"

namespace SDK
{
	struct Player;
	struct PlayerStamina;

	struct LocalPlayerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		Player* Player;
		void* journalController;
		Camera* Camera;
		bool Field3;
		char pad_000[0x7];
		GameObject* Field4;
		void* playerCharacterAnimations;
		void* playerGraphics;
		LocalPlayerVoice* voice;
		void* breath;
		bool Field9;
		char pad_001[0x7];
		void* playerInput;
		void* photonView;
		void* localHeadMountedSocket;
		void* physicsCharacterController;
		float Field14;
		float Field15;
		float Field16;
		float Field17;
		PlayerStamina* stamina;
	};

	struct LocalPlayer
	{
		void* Clazz;
		void* Monitor;
		LocalPlayerFields Fields;
	};

	DEC_MET(LocalPlayer_TeleportPlayer, void(*)(LocalPlayer* player, Vector3 position, MethodInfo* methodInfo), "Assembly-CSharp", "", "LocalPlayer", "TeleportPlayer", 1);
}
#pragma once
#include "sdk.h"

namespace SDK
{
	// class PlayerVoice
	struct PlayerVoiceFields
	{
		MonoBehaviourFields monoBehaviourFields;
		void* player;
		void* playerAudio;
		void* audioSource;
		bool isPressingPushToTalk;
		bool isMicrophoneActive;
	};

	struct PlayerVoice
	{
		void* Clazz;
		void* Monitor;
		PlayerVoiceFields Fields;
	};

	// class LocalPlayerVoice
	struct LocalPlayerVoiceFields
	{
		MonoBehaviourFields monoBehaviourFields;
		PlayerVoice* playerVoice;
	};

	struct LocalPlayerVoice
	{
		void* Clazz;
		void* Monitor;
		LocalPlayerVoiceFields Fields;
	};
}
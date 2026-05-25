#pragma once
#include "sdk.h"

namespace SDK
{
	enum KeyType : int32_t
	{
		None,
		Main,
		Secondary,
		PermanentLock
	};

	struct KeyInfoFields
	{
		char pad_000[0x8]; // ScriptableObject
		KeyType keyType;
	};

	struct KeyInfo
	{
		void* Clazz;
		void* Monitor;
		KeyInfoFields Fields;
	};

	struct KeyFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		void* photonInteraction;
		KeyInfo* info;
	};

	struct Key
	{
		void* Clazz;
		void* Monitor;
		KeyFields Fields;
	};

	DEC_MET(Key_Start, void(*)(Key* key, MethodInfo* methodInfo), "Assembly-CSharp", "", "Key", "Start", 0)
	DEC_MET(Key_GrabbedKey, void(*)(Key* key, MethodInfo* methodInfo), "Assembly-CSharp", "", "Key", "GrabbedKey", 0)
}

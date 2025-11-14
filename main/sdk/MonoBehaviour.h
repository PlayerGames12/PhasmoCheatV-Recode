#pragma once
#include "sdk.h"

namespace SDK
{
	struct MethodInfo;

	struct __declspec(align(8)) Object1Fields
	{
		void* m_CachedPtr;
		void* m_CancellationTokenSource;
	};

	struct Component1Fields
	{
		Object1Fields _;
	};

	struct BehaviourFields
	{
		Component1Fields _;
	};

	struct Behaviour
	{
	};

	struct MonoBehaviourFields
	{
		BehaviourFields _;
	};

	struct MonoBehaviour
	{
		void* Clazz;
		void* Monitor;
		MonoBehaviourFields Fields;
	};

	struct MonoBehaviourPunFields
	{
		MonoBehaviourFields _;
		void* pvCache;
	};

	struct MonoBehaviourPunCallbacksFields
	{
		MonoBehaviourPunFields _;
	};

	DEC_MET(Behaviour_Set_Enabled, void(*)(Behaviour* behaviour, bool enabled, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Behaviour", "set_enabled", 1);
}

#pragma once
#include "sdk.h"

namespace SDK
{
	struct NavMeshAgent;
	struct NavMeshPath;

	struct Vector3Array
	{
		void* Clazz;
		void* Monitor;
		void* Bounds;
		uint32_t MaxLenght;
		Vector3 Vector[1];
		char pad_000[0x4];
	};

	// class NavMeshAgent
	DEC_MET(NavMeshAgent_get_speed, float(*)(NavMeshAgent* navMeshAgent, MethodInfo* methodInfo), "UnityEngine.AIModule", "UnityEngine.AI", "NavMeshAgent", "get_speed", 0);
	DEC_MET(NavMeshAgent_get_path, NavMeshPath* (*)(NavMeshAgent* navMeshAgent, MethodInfo* methodInfo), "UnityEngine.AIModule", "UnityEngine.AI", "NavMeshAgent", "get_path", 0);
	
	// class NavMeshPath
	DEC_MET(NavMeshPath_get_corners, Vector3Array* (*)(NavMeshPath* navMeshPath, MethodInfo* methodInfo), "UnityEngine.AIModule", "UnityEngine.AI", "NavMeshPath", "get_corners", 0)
}
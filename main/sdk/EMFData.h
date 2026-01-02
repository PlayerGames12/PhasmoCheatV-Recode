#pragma once
#include "sdk.h"

namespace SDK
{
	struct EMFDataFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		LineRenderer* Rend;
		void* Screen;
		void* GlitchText;
		void* EMFSpots;
		Transform* StartingPos;
	};

	struct EMFData
	{
		void* Clazz;
		void* Monitor;
		EMFDataFields Fields;
	};

	DEC_MET(EMFData_Start, void(*)(SDK::EMFData* emfData, SDK::MethodInfo* methodInfo), "Assembly-CSharp", "", "EMFData", "Start", 0);
	DECLARE_PATTERN_POINTER_MORE(EMFData_UpdateNightMareGraph, void(*)(SDK::EMFData* emfData, SDK::MethodInfo* methodInfo), L"GameAssembly.dll", "il2cpp", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 41 ? 33 FF 0F 29 74 24 ? 48 8B D9", 6);
	DECLARE_PATTERN_POINTER(EMFData_UpdateGraph, void(*)(SDK::EMFData* emfData, SDK::MethodInfo* methodInfo), L"GameAssembly.dll", "il2cpp", "48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 0F 29 74 24 ? 48 8B F9 F3 0F 10 35");
}

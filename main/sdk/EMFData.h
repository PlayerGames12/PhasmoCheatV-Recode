#pragma once
#include "sdk.h"

namespace SDK
{
	struct EMF;

	struct EMFSpotsArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds;
		uint32_t MaxLength;
		EMF* Vector[1];
	};

	struct __declspec(align(8)) EMFSpotsListFields
	{
		EMFSpotsArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot;
	};

	struct ListEMFSpots
	{
		void* Clazz;
		void* Monitor;
		EMFSpotsListFields Fields;
	};

	struct EMFDataFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		LineRenderer* Rend;
		void* Screen;
		void* GlitchText;
		ListEMFSpots* EMFSpots;
		Transform* StartingPos;
	};

	struct EMFData
	{
		void* Clazz;
		void* Monitor;
		EMFDataFields Fields;
	};

	struct EMFData_staticFields
	{
		EMFData* instance;
	};

	DEC_MET(EMFData_Start, void(*)(SDK::EMFData* emfData, SDK::MethodInfo* methodInfo), "Assembly-CSharp", "", "EMFData", "Start", 0);
	DEC_SFIELD(EMFData_sFields, EMFData_staticFields, "Assembly-CSharp", "", "EMFData");
	DECLARE_PATTERN_POINTER(EMFData_UpdateNightMareGraph, void(*)(SDK::EMFData* emfData, SDK::MethodInfo* methodInfo), L"GameAssembly.dll", "il2cpp", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 41 ? 33 FF 0F 29 74 24 ? 48 8B D9 8B F7"); // 2 in HowFindMethods
	DECLARE_PATTERN_POINTER(EMFData_UpdateGraph, void(*)(SDK::EMFData* emfData, SDK::MethodInfo* methodInfo), L"GameAssembly.dll", "il2cpp", "48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 0F 29 74 24 ? 48 8B F9 F3 0F 10 35"); // 3 in HowFindMethods
}

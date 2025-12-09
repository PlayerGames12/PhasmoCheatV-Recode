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
}

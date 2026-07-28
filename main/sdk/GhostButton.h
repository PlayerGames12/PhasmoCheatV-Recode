#pragma once
#include "sdk.h"

namespace SDK
{
	struct GhostButtonFields
	{
		ThreeStateButtonFields threeStateButtonFields;
		GhostType ghostType;
		void* scratchImage;
		void* scratchSprites;
		bool scratched;
	};

	struct GhostButton
	{
		void* Clazz;
		void* Monitor;
		GhostButtonFields Fields;
	};

	DECLARE_PATTERN_POINTER(GhostButton_OnClick, void(*)(GhostButton* ghostButton, MethodInfo* methodInfo), L"GameAssembly.dll", "il2cpp", "40 53 48 83 EC ? 48 8B D9 48 8B 49 ? 48 85 C9 74 ? 45 33 C0 48 8B D3 E8 ? ? ? ? 33 D2"); // 5 in HowFindMethods
}
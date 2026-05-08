#pragma once
#include "sdk.h"

namespace SDK
{
	struct LocalPCPlayerFields
	{
		char* pad_000[0xF8]; // LocalPlayer fields
		void* localJournalController;
		void* pCControls;
		void* pCCanvas;
		FirstPersonController* firstPersonController;
	};

	struct LocalPCPlayer
	{
		void* Clazz;
		void* Monitor;
		LocalPCPlayerFields Fields;
	};
}
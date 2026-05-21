#pragma once
#include "sdk.h"

namespace SDK
{
	struct JournalMediaArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds;
		uint32_t max_length;
		JournalMedia* vector[1];
	};

	struct Journal_PhotoPageFields
	{
		MonoBehaviourPunFields monoBehaviourPunFields;
		void* journalController;
		JournalMediaArray* photosArray;
	};

	struct Journal_PhotoPage
	{
		void* Clazz;
		void* Monitor;
		Journal_PhotoPageFields Fields;
	};
}
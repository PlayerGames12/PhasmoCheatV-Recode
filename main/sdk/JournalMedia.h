#pragma once
#include "sdk.h"

namespace SDK
{
	struct JournalMediaFields
	{
		char pad_000[0x90];
		Media* media;
	};

	struct JournalMedia
	{
		void* Clazz;
		void* Monitor;
		JournalMediaFields Fields;
	};
}
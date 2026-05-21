#pragma once
#include "sdk.h"

namespace SDK
{
	struct MediaFields
	{
		MediaValues* value;
	};

	struct Media
	{
		void* Clazz;
		void* Monitor;
		MediaFields Fields;
	};
}
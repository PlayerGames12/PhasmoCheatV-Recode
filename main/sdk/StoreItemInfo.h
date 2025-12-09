#pragma once
#include "../Includes.h"

namespace SDK
{
	struct StoreItemInfoFields
	{
		ItemInfoFields ItemInfoFields;
	};

	struct StoreItemInfo
	{
		void* Clazz;
		void* Monitor;
		StoreItemInfoFields Fields;
	};
}
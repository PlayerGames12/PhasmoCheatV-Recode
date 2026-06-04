#pragma once
#include "sdk.h"

namespace SDK
{
	struct EMFFields
	{
		MonoBehaviourFields monobehaviourFields;
		void* evidenceComponent;
		int32_t strenght;
	};

	struct EMF
	{
		void* Clazz;
		void* Monitor;
		EMFFields Fields;
	};
}
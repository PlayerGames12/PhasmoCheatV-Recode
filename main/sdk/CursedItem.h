#pragma once
#include "sdk.h"

namespace SDK
{
	struct CursedItem;

	DEC_MET(CursedItem_Use, void(*)(CursedItem* cursedItem, MethodInfo* methodInfo), "Assembly-CSharp", "", "CursedItem", "Use", 0);
	DEC_MET(CursedItem_BreakItem, void(*)(CursedItem* cursedItem, MethodInfo* methodInfo), "Assembly-CSharp", "", "CursedItem", "BreakItem", 0);
}

#pragma once
#include "sdk.h"

namespace SDK
{
	struct JournalController;

	DEC_MET(JournalController_SelectGhost, void(*)(JournalController* journalController, GhostType ghostType, MethodInfo* methodInfo), "Assembly-CSharp", "", "JournalController", "SelectGhost", 1);
}

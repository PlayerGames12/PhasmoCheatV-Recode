#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkJournalController_SendState(SDK::JournalController* journalController, bool a1, bool sync, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called JournalController_SendState");

	//todo: add new feature: Unsync journal (this looks funny)
	//if (CheatWork)
	//	sync = false;

	SDK::JournalController_SendState_original(journalController, a1, sync, methodInfo);
}
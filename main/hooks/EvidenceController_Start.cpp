#include "../Includes.h"

void Hooks::hkEvidenceController_Start(SDK::EvidenceController* evidenceController, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called EvidenceController_Start");

	if (CheatWork)
		InGame::evidenceController = evidenceController;

	SDK::EvidenceController_Start(evidenceController, methodInfo);
}
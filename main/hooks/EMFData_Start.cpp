#include "../Includes.h"

void Hooks::hkEMFData_Start(SDK::EMFData* emfData, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called EvidenceController_Start");

	if (CheatWork)
		InGame::emfData = emfData;

	SDK::EMFData_Start(emfData, methodInfo);
}
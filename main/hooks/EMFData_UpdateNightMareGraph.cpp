#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkEMFData_UpdateNightMareGraph(SDK::EMFData* emfData, SDK::MethodInfo* methodInfo)
{
	LOG_CALL_UPDATE("Caleld EMFData_UpdateNightMareGraph");

	auto* func = SDK::Get_EMFData_UpdateGraph();
	func(emfData, nullptr);
}
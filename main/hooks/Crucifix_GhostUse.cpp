#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkCrucifix_GhostUse(SDK::Crucifix* crucifix, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called Crucifix_GhostUse");

	SDK::Crucifix_GhostUse(crucifix, methodInfo);

	if (CheatWork)
		CALL_METHOD_IF_ACTIVE_ARGS(Misc, CrucifixModifier, CrucifixModifierHook, crucifix);
}
#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkDNAEvidence_GrabbedNetworked(SDK::DNAEvidence* dnaEvidence, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called DNAEvidence_GrabbedNetworked");

	CALL_METHOD(Visuals, NotifyInfo, RenderNotifyBone);

	SDK::DNAEvidence_GrabbedNetworked(dnaEvidence, methodInfo);
}
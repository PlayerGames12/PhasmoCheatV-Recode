#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;
using namespace PhasmoCheatV::Features::Ghost;

void Hooks::hkGhostInfo_SyncEvidence(SDK::GhostInfo* instance, int* evidence, void* photon, SDK::MethodInfo* methodInfo)
{
    LOG_CALL("Called GhostInfo_SyncEvidence");

    CALL_METHOD_IF_ACTIVE_ARGS(Ghost, GhostDesigner, ApplyGhostEvidence, evidence);

    SDK::GhostInfo_SyncEvidence(instance, evidence, photon, methodInfo);
}
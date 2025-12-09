#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkObjectiveManager_Update(SDK::ObjectiveManager* objectiveManager, SDK::MethodInfo* methodInfo)
{
    LOG_CALL_UPDATE("Called ObjectiveManager_Update");

    CALL_METHOD_IF_ACTIVE_ARGS(Misc, RewardModifier, RewardModifierObjectives, objectiveManager);

    SDK::ObjectiveManager_Update(objectiveManager, methodInfo);
}
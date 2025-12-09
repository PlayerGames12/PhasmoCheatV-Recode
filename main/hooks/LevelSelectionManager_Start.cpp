#include "../Includes.h"
#include "../features/features_includes.h"

std::nullptr_t Hooks::hkLevelSelectionManager_Start(SDK::LevelSelectionManager* levelSelectionManager, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called LevelSelectionManager_Start");

	CALL_METHOD_ARGS(Map, MapModifier, MapModifierMainAutoVote, levelSelectionManager);

	return SDK::LevelSelectionManager_Start(levelSelectionManager, methodInfo);
}
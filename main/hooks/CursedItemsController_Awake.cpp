#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkCursedItemsController_Awake(SDK::CursedItemsController* cursedItemsController, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called CursedItemsController_Awake");

	if (CheatWork)
		InGame::cursedItemsController = cursedItemsController;

	SDK::CursedItemsController_Awake(cursedItemsController, methodInfo);
}
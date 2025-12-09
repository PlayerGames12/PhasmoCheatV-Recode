#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkFirstPersonController_Update(SDK::FirstPersonController* firstPersonController, SDK::MethodInfo* methodInfo)
{
	LOG_CALL_UPDATE("Called FirstPersonController_Update");

	SDK::FirstPersonController_Update(firstPersonController, methodInfo);

	CALL_METHOD_ARGS(Players, CustomLookLimits, CustomLookLimitsMain, firstPersonController);
	CALL_METHOD_IF_ACTIVE(Players, FoVEditor, FoVEditorMain);
	CALL_METHOD_IF_ACTIVE_ARGS(Movement, NoClip, NoClipMain, firstPersonController);
	CALL_METHOD_ARGS(Movement, CustomSpeed, CustomSpeedMain, firstPersonController);

	CALL_METHOD_IF_ACTIVE(Visuals, Fullbright, FullbrightMain);
}
#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkGhostAI_Update(SDK::GhostAI* ghostAI, SDK::MethodInfo* methodInfo)
{
	LOG_CALL_UPDATE("Called GhostAI_Update");

	SDK::GhostAI_Update(ghostAI, methodInfo);

	// EXAMPLE CALL: CALL_METHOD(Visuals, Watermark, OnRender);

	CALL_METHOD(Ghost, GhostModifier, GhostModifierMain);
	CALL_METHOD(Ghost, GhostInteractor, GhostInteractorMain);
	CALL_METHOD(Players, Pickup, PickupMain);
	CALL_METHOD(Map, GrabKeys, GrabKeysMain);
	CALL_METHOD(Map, MapModifier, MapModifierMain);
	CALL_METHOD(Map, SaltModifier, SaltModifierMain);
	CALL_METHOD(Visuals, StatsPanel, StatsPanelCollectBone);

	if (ForTestsFlag && IsDebugging)
		Test::TestFeatures1();
}
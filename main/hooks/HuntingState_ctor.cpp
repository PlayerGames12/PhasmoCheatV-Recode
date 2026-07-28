#include "../Includes.h"

using namespace PhasmoCheatV;

void Hooks::hkHuntingState_ctor(SDK::HuntingState* huntingState, SDK::GhostAI* ghostAI, void* navMeshAgent, SDK::PhotonView* photonView, bool force, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called HuntingState_ctor");

	if (CheatWork)
		InGame::huntingState = huntingState;

	SDK::HuntingState_ctor_original(huntingState, ghostAI, navMeshAgent, photonView, force, methodInfo);
}
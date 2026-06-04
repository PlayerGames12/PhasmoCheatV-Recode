#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

void Hooks::hkDNAEvidence_Start(SDK::DNAEvidence* dnaEvidence, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called DNAEvidence_Start");

	if (GET_ACTIVE(Auto, AutoPickupBone))
	{
		auto* g_obj = SDK::Component_Get_GameObject((SDK::Component*)(dnaEvidence), nullptr); 
		if (!g_obj)
		{
			SDK::DNAEvidence_Start(dnaEvidence, methodInfo);
			return;
		}

		auto* pvType = SDK::System_Type_GetType(Utils::SysStrToUnityStr("Photon.Pun.PhotonView"), nullptr);
		auto* photonView = (SDK::PhotonView*)(SDK::GameObject_GetComponent(g_obj, pvType, nullptr));
		if (!photonView)
		{
			SDK::DNAEvidence_Start(dnaEvidence, methodInfo);
			return;
		}

		SDK::PhotonView_RPC(photonView, Utils::SysStrToUnityStr("GrabbedNetworked"), SDK::RpcTarget::All, nullptr, nullptr);
	}

	SDK::DNAEvidence_Start(dnaEvidence, methodInfo);
}
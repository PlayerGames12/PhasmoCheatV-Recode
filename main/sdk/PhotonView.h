#pragma once
#include "sdk.h"

namespace SDK
{
	struct PhotonView;

	DEC_MET(PhotonView_RequestOwnership, void(*)(PhotonView* photonView, MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonView", "RequestOwnership", 0);
}
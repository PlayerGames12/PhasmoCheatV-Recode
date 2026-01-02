#pragma once
#include "sdk.h"

namespace SDK
{
	struct PhotonMessageInfo;

    DEC_MET(PhotonMessageInfo_get_timestamp, double(*)(PhotonMessageInfo* instance, MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonMessageInfo", "get_timestamp", 0);
}

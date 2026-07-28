#pragma once
#include "sdk.h"

namespace SDK
{
	struct PhotonView;
	struct PRPlayer;

	struct PhotonMessageInfoFields
	{
		int32_t timeInt;
		char pad_000[0x4];
		PRPlayer* Sender;
		PhotonView* photonView;
	};

	struct PhotonMessageInfo
	{
		PhotonMessageInfoFields Fields;
	};

    DEC_MET(PhotonMessageInfo_get_timestamp, double(*)(PhotonMessageInfo* instance, MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonMessageInfo", "get_timestamp", 0);
}

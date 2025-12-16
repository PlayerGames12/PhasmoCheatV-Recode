#pragma once
#include "sdk.h"

namespace SDK
{
	struct PhotonNetwork
	{
	};

	DEC_MET(PhotonNetwork_GetPing, int(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "GetPing", 0);
	DEC_MET(PhotonNetwork_Get_IsMasterClient, bool(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_IsMasterClient", 0);
	DEC_MET(PhotonNetwork_Get_MasterClient, Player* (*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_MasterClient", 0);
	DEC_MET(PhotonNetwork_Get_IsConnected, bool(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_IsConnected", 0);
	DEC_MET(PhotonNetwork_Set_NickName, void(*)(String* nickName, MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "set_NickName", 1);
	DEC_MET(PhotonNetwork_Get_LocalPlayer, Player* (*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_LocalPlayer", 0);	
}

#pragma once
#include "sdk.h"

namespace SDK
{
	struct PhotonNetwork;

	struct PRPlayerFields
	{
		void* roomReference;
		int32_t actorNumber;
		bool isLocal;
		bool hasRejoined;
		char pad_000[0x2];
		String* nickName;
		String* _userId;
		bool isInactive;
		char pad_001[0x7];
		void* _customProperties;
		void* TagObject;
	};

	struct PRPlayer // Photon.Realtime.Player
	{
		void* Clazz;
		void* Monitor;
		PRPlayerFields Fields;
	};

	DEC_MET(PhotonNetwork_GetPing, int(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "GetPing", 0);
	DEC_MET(PhotonNetwork_Get_IsMasterClient, bool(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_IsMasterClient", 0);
	DEC_MET(PhotonNetwork_Get_MasterClient, Player* (*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_MasterClient", 0);
	DEC_MET(PhotonNetwork_Get_IsConnected, bool(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_IsConnected", 0);
	DEC_MET(PhotonNetwork_Set_NickName, void(*)(String* nickName, MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "set_NickName", 1);
	DEC_MET(PhotonNetwork_Get_LocalPlayer, Player* (*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_LocalPlayer", 0);	
	DEC_MET(PhotonNetwork_Get_ServerTimestamp, int(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_ServerTimestamp", 0);
	DEC_MET(PhotonNetwork_Get_InRoom, bool(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_InRoom", 0);
	DEC_MET(PhotonNetwork_Get_OfflineMode, bool(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_OfflineMode", 0);

	// Photon.Realtime.Player | im lazy for create new sdk file 
	DEC_MET(PRPlayer_get_ActorNumber, int32_t(*)(PRPlayer* prpPlayer, MethodInfo* methodInfo), "PhotonRealtime", "Photon.Realtime", "Player", "get_ActorNumber", 0);
}

#pragma once
#include "sdk.h"

namespace SDK
{
	struct ServerManagerFields
	{
		char pad_000[0xD0];
		TextMeshProUGUI* readyText;
	};

	struct ServerManager
	{
		void* Clazz;
		void* Monitor;
		ServerManagerFields Fields;
	};

	DEC_MET(ServerManager_KickPlayerNetworked, void(*)(ServerManager* serverManager, bool isBanned, void* photonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "ServerManager", "KickPlayerNetworked", 2);
	DEC_MET(ServerManager_StartGame, void(*)(ServerManager* serverManager, MethodInfo* methodInfo), "Assembly-CSharp", "", "ServerManager", "StartGame", 0);
	DEC_MET(ServerManager_Ready, void(*)(ServerManager* serverManager, bool on, MethodInfo* methodInfo), "Assembly-CSharp", "", "ServerManager", "Ready", 1);
}

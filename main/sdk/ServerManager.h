#pragma once
#include "sdk.h"

namespace SDK
{
	struct ServerManager;

	DEC_MET(ServerManager_KickPlayerNetworked, void(*)(ServerManager* serverManager, bool isBanned, void* photonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "ServerManager", "KickPlayerNetworked", 2);
}

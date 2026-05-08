#pragma once
#include "sdk.h"

namespace SDK
{
	DEC_MET(SteamFriends_GetPersonalName, String*(*)(MethodInfo* methodInfo), "com.rlabrecque.steamworks.net", "Steamworks", "SteamFriends", "GetPersonaName", 0);
	DEC_MET(SteamFriends_SetRichPresence, bool(*)(String* pchKey, String* pchValue, MethodInfo* methodInfo), "com.rlabrecque.steamworks.net", "Steamworks", "SteamFriends", "SetRichPresence", 2);

	// Steam API
	DEC_MET(SteamAPI_Init, bool(*)(MethodInfo* methodInfo), "com.rlabrecque.steamworks.net", "Steamworks", "SteamAPI", "Init", 0);
}
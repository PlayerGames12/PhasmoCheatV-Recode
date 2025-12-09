#pragma once
#include "sdk.h"

namespace SDK
{
	struct Network;

	struct __declspec(align(8)) NetworkPlayerSpotFields
	{
		bool PlayerReady;
		int PlayerCharacterIndex;
		void* PhotonPlayer;
		String* UnityPlayerID;
		int Experience;
		int Level;
		int Prestige;
		Player* Player;
		float PlayerVolume;
		String* AccountName;
		bool IsKicked;
		bool IsHacker;
		bool IsBlocked;
		void* RoleBadges;
		void* Role;
		int PrestigeIndex;
		bool PrestigeTheme;
		void* VotedContract;
		int32_t PlatformType;
		bool HasReceivedPlayerInformation;
		bool PlayerIsBlocked;
		int32_t LegacyLevel;
		int32_t LegacyAccent;
		int32_t LegacyBackground;
		int32_t LegacyColor;
		void* PlayerEquipment;
		bool hasBroughtItems;
		int32_t totalEquipmentCost;
		void* OnBlockMuteStateChanged;
	};

	struct NetworkPlayerSpot
	{
		void* Clazz;
		void* Monitor;
		NetworkPlayerSpotFields Fields;
	};

	struct NetworkPlayerSpotArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds;
		void* MaxLength;
		NetworkPlayerSpot* Vector[32];
	};

	struct __declspec(align(8)) ListNetworkPlayerSpotFields
	{
		NetworkPlayerSpotArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot;
	};

	struct ListNetworkPlayerSpot
	{
		void* Clazz;
		void* Monitor;
		ListNetworkPlayerSpotFields Fields;
	};

	struct NetworkFields
	{
		MonoBehaviourPunCallbacksFields MonoBehaviourPunCallbacksFields;
		Player* localPlayer;
		ListNetworkPlayerSpot* NetworkPlayerSpots;
	};

	struct Network
	{
		void* Clazz;
		void* Monitor;
		NetworkFields Fields;
	};

	DEC_MET(Network_Get_Network, Network* (*)(MethodInfo* methodInfo), "Assembly-CSharp", "", "Network", "get_Instance", 0);
}

#pragma once
#include "sdk.h"

namespace SDK
{
	struct Network;
	struct LocalPCPlayer;

	struct __declspec(align(8)) NetworkPlayerSpotFields
	{
		bool PlayerReady;            // 0x10
		char pad_11[0x7];            // до 0x18

		void* PhotonPlayer;          // 0x18
		String* UnityPlayerID;       // 0x20

		int Experience;              // 0x28
		int Level;                   // 0x2C
		int Prestige;                // 0x30
		char pad_34[0x4];            // до 0x38

		Player* Player;              // 0x38
		float PlayerVolume;          // 0x40
		char pad_44[0x4];            // до 0x48

		String* AccountName;         // 0x48

		bool IsKicked;               // 0x50
		bool IsHacker;               // 0x51
		bool IsBlocked;              // 0x52
		char pad_53[0x5];            // до 0x58

		void* RoleBadges;            // 0x58
		void* Role;                  // 0x60

		int PrestigeIndex;           // 0x64
		int ThemeIndex;              // 0x68
		char pad_6C[0x4];            // до 0x70

		void* VotedContract;         // 0x70
		int32_t PlatformType;        // 0x78

		bool HasReceivedPlayerInformation; // 0x7C
		bool PlayerIsBlocked;              // 0x7D
		char pad_7E[0x2];                  // до 0x80

		int32_t LegacyLevel;         // 0x80
		int32_t LegacyAccent;        // 0x84
		int32_t LegacyBackground;    // 0x88
		int32_t LegacyColor;         // 0x8C

		void* PlayerCosmetics;       // 0x90
		void* PlayerEquipment;       // 0x98

		bool hasBroughtItems;        // 0xA0
		char pad_A1[0x3];            // до 0xA4

		int32_t totalEquipmentCost;  // 0xA4
		void* OnBlockMuteStateChanged; // 0xA8
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
		LocalPlayer* localPlayer_;
		ListNetworkPlayerSpot* NetworkPlayerSpots;
	};

	struct Network
	{
		void* Clazz;
		void* Monitor;
		NetworkFields Fields;
	};

	DEC_MET(Network_Get_Network, Network* (*)(MethodInfo* methodInfo), "Assembly-CSharp", "", "Network", "get_Instance", 0);
	DEC_MET(Network_get_nonNetworkedPCPlayer, LocalPCPlayer* (*)(Network* network, MethodInfo* methodInfo), "Assembly-CSharp", "", "Network", "get_nonNetworkedPCPlayer", 0);
}

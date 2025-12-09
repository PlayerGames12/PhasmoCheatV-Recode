#pragma once
#include "../Includes.h"
#include "../sdk/sdk.h"

using namespace PhasmoCheatV;

namespace Utils {
	std::string GetPhasmoCheatVDirectory();
	void CreatePhasmoCheatVDirectory();
	SDK::NetworkPlayerSpot* GetNetworkPlayerSpot(const SDK::Player* player);
	SDK::Network* GetNetwork();
	SDK::Player* GetLocalPlayer();
	std::string getKeyName(int keyCode);
	std::string GhostEnumToStr(SDK::GhostState ghostState);
	std::string GhostEnumToStr(SDK::GhostType ghostType);
	std::string GhostEnumToStr(const SDK::GhostEvidence ghostEvidence);
	std::string UnityStrToSysStr(const SDK::String& string);
	SDK::String* SysStrToUnityStr(const std::string& string);
	std::string GetPlayerName(const SDK::Player* player);
	SDK::ListPlayer* GetAllPlayers();
	int GetPlayerInx(const SDK::Player* player);
	bool WTS(const SDK::Vector3& worldPos, SDK::Vector3& displayPos);
	SDK::Vector3 GetPosVec3(const SDK::Player* player);
	SDK::Vector3 GetPosVec3(const SDK::GhostAI* ghostAI);
	SDK::Vector3 GetPosVec3(SDK::Component* component);
	SDK::Vector3 GetPosVec3(SDK::Transform* transform);
	std::string GhostEnumToStr(SDK::EvidenceType evidenceType);
	bool IsCursedItem(SDK::EvidenceType evidenceType);
	SDK::Transform* GetPlayerTransformCamera(const SDK::Player* player);
	SDK::LevelStats* GetLevelStats();
	double GetCheatUptimeSeconds();
	float GetPlayerSanity(SDK::Player* player);
	bool IsLocalMasterClient();
	void TpPlayerToVec3(SDK::Player* player, const SDK::Vector3& position);
	void TpPlayerToPlayer(SDK::Player* player, const SDK::Player* twoplayer);
	SDK::LevelValues* GetLevelValues();
	SDK::Map* GetMap();
	std::string GetActiveSceneName();
	SDK::GameObject* FindObjectByName(std::string name);
	SDK::StoreItemInfo* GetStoreItemInfo();
	SDK::ObjectArray* FindObjectsByName();
}
#include "utils.h"

using namespace PhasmoCheatV;

std::string Utils::GetPhasmoCheatVDirectory()
{
	return "C:\\PhasmoCheatV";
}

void Utils::CreatePhasmoCheatVDirectory()
{
	const std::string configDirectoryPath = GetPhasmoCheatVDirectory();
	if (std::filesystem::exists(configDirectoryPath))
		return;

	LOG_INFO("PhasmoCheatV directory not found, creating one.");
	std::filesystem::create_directory(configDirectoryPath);
}

SDK::Network* Utils::GetNetwork()
{
	if (InGame::network)
		return InGame::network;

	SDK::Network* network = SDK::Network_Get_Network(nullptr);

	if (network == nullptr)
		return nullptr;

	InGame::network = network;

	return network;
}

SDK::ListPlayer* Utils::GetAllPlayers()
{
	if (InGame::mapController == nullptr)
		return nullptr;

	return InGame::mapController->Fields.Players;
}

int Utils::GetPlayerInx(const SDK::Player* player)
{
	const auto players = GetAllPlayers();
	if (!players)
		return -1;

	for (int playerIndex = 0; playerIndex < players->Fields.Size; playerIndex++)
	{
		if (players->Fields.Items->Vector[playerIndex] == player)
			return playerIndex;
	}

	return -1;
}

SDK::NetworkPlayerSpot* Utils::GetNetworkPlayerSpot(const SDK::Player* player)
{
	if (!GetNetwork())
		return nullptr;

	return InGame::network->Fields.NetworkPlayerSpots->Fields.Items->Vector[GetPlayerInx(player)];
}

SDK::Player* Utils::GetLocalPlayer()
{
	if (!GetNetwork())
		return nullptr;
	return InGame::network->Fields.localPlayer;
}

std::string Utils::getKeyName(int keyCode)
{
	switch (keyCode)
	{
	case VK_INSERT: return "INSERT";
	case VK_DELETE: return "DELETE";
	case VK_HOME: return "HOME";
	case VK_END: return "END";
	case VK_PRIOR: return "PAGE UP";
	case VK_NEXT: return "PAGE DOWN";
	case VK_F1: return "F1";
	case VK_F2: return "F2";
	case VK_F3: return "F3";
	case VK_F4: return "F4";
	case VK_F5: return "F5";
	case VK_F6: return "F6";
	case VK_F7: return "F7";
	case VK_F8: return "F8";
	case VK_F9: return "F9";
	case VK_F10: return "F10";
	case VK_F11: return "F11";
	case VK_F12: return "F12";
	case VK_RETURN: return "Enter";
	default:
		if (keyCode >= 'A' && keyCode <= 'Z')
			return std::string(1, (char)keyCode);
		else if (keyCode >= '0' && keyCode <= '9')
			return std::string(1, (char)keyCode);
		else
			return "Key " + std::to_string(keyCode);
	}
}


std::string Utils::GhostEnumToStr(SDK::GhostState ghostState)
{
	std::string ghostStateString;

	switch (ghostState)
	{
	case SDK::GhostState::Idle:
		ghostStateString = "Idle";
		break;
	case SDK::GhostState::Wander:
		ghostStateString = "Wander";
		break;
	case SDK::GhostState::Hunting:
		ghostStateString = "Hunting";
		break;
	case SDK::GhostState::FavoriteRoom:
		ghostStateString = "Favorite Room";
		break;
	case SDK::GhostState::Light:
		ghostStateString = "Light";
		break;
	case SDK::GhostState::Door:
		ghostStateString = "Door";
		break;
	case SDK::GhostState::Throwing:
		ghostStateString = "Throwing";
		break;
	case SDK::GhostState::FuseBox:
		ghostStateString = "Fuse Box";
		break;
	case SDK::GhostState::Appear:
		ghostStateString = "Appear";
		break;
	case SDK::GhostState::DoorKnock:
		ghostStateString = "Door Knock";
		break;
	case SDK::GhostState::WindowKnock:
		ghostStateString = "Window Knock";
		break;
	case SDK::GhostState::CarAlarm:
		ghostStateString = "Car Alarm";
		break;
	case SDK::GhostState::Flicker:
		ghostStateString = "Flicker";
		break;
	case SDK::GhostState::CCTV:
		ghostStateString = "CCTV";
		break;
	case SDK::GhostState::RandomEvent:
		ghostStateString = "Random Event";
		break;
	case SDK::GhostState::GhostAbility:
		ghostStateString = "Ghost Ability";
		break;
	case SDK::GhostState::Mannequin:
		ghostStateString = "Mannequin";
		break;
	case SDK::GhostState::TeleportObject:
		ghostStateString = "Teleport Object";
		break;
	case SDK::GhostState::Interact:
		ghostStateString = "Interact";
		break;
	case SDK::GhostState::SummoningCircle:
		ghostStateString = "Summoning Circle";
		break;
	case SDK::GhostState::MusicBox:
		ghostStateString = "Music Box";
		break;
	case SDK::GhostState::Dots:
		ghostStateString = "Dots";
		break;
	case SDK::GhostState::Salt:
		ghostStateString = "Salt";
		break;
	default:
		ghostStateString = "Unknown";
		break;
	}

	return ghostStateString;
}

std::string Utils::GhostEnumToStr(SDK::GhostType ghostType)
{
	std::string ghostTypeString;

	switch (ghostType)
	{
	case SDK::GhostType::Spirit:
		ghostTypeString = "Spirit";
		break;
	case SDK::GhostType::Wraith:
		ghostTypeString = "Wraith";
		break;
	case SDK::GhostType::Phantom:
		ghostTypeString = "Phantom";
		break;
	case SDK::GhostType::Poltergeist:
		ghostTypeString = "Poltergeist";
		break;
	case SDK::GhostType::Banshee:
		ghostTypeString = "Banshee";
		break;
	case SDK::GhostType::Jinn:
		ghostTypeString = "Jinn";
		break;
	case SDK::GhostType::Mare:
		ghostTypeString = "Mare";
		break;
	case SDK::GhostType::Revenant:
		ghostTypeString = "Revenant";
		break;
	case SDK::GhostType::Shade:
		ghostTypeString = "Shade";
		break;
	case SDK::GhostType::Demon:
		ghostTypeString = "Demon";
		break;
	case SDK::GhostType::Yurei:
		ghostTypeString = "Yurei";
		break;
	case SDK::GhostType::Oni:
		ghostTypeString = "Oni";
		break;
	case SDK::GhostType::Yokai:
		ghostTypeString = "Yokai";
		break;
	case SDK::GhostType::Hantu:
		ghostTypeString = "Hantu";
		break;
	case SDK::GhostType::Goryo:
		ghostTypeString = "Goryo";
		break;
	case SDK::GhostType::Myling:
		ghostTypeString = "Myling";
		break;
	case SDK::GhostType::Onryo:
		ghostTypeString = "Onryo";
		break;
	case SDK::GhostType::TheTwins:
		ghostTypeString = "The Twins";
		break;
	case SDK::GhostType::Raiju:
		ghostTypeString = "Raiju";
		break;
	case SDK::GhostType::Obake:
		ghostTypeString = "Obake";
		break;
	case SDK::GhostType::Mimic:
		ghostTypeString = "Mimic";
		break;
	case SDK::GhostType::Moroi:
		ghostTypeString = "Moroi";
		break;
	case SDK::GhostType::Deogen:
		ghostTypeString = "Deogen";
		break;
	case SDK::GhostType::Thaye:
		ghostTypeString = "Thaye";
		break;
	default:
		ghostTypeString = "Unknown";
		break;
	}

	return ghostTypeString;
}

std::string Utils::GhostEnumToStr(const SDK::GhostEvidence ghostEvidence)
{
	std::string evidenceTypeString;

	switch (ghostEvidence)
	{
	case SDK::GhostEvidence::None:
		evidenceTypeString = "None";
		break;
	case SDK::GhostEvidence::EMF:
		evidenceTypeString = "EMF Level 5";
		break;
	case SDK::GhostEvidence::SpiritBox:
		evidenceTypeString = "Spirit Box";
		break;
	case SDK::GhostEvidence::Ultraviolet:
		evidenceTypeString = "Ultraviolet";
		break;
	case SDK::GhostEvidence::GhostOrb:
		evidenceTypeString = "Ghost Orb";
		break;
	case SDK::GhostEvidence::GhostWritingBook:
		evidenceTypeString = "Ghost Writing";
		break;
	case SDK::GhostEvidence::Temperature:
		evidenceTypeString = "Freezing Temperature";
		break;
	case SDK::GhostEvidence::DotsProjector:
		evidenceTypeString = "D.O.T.S. Projector";
		break;
	default:
		evidenceTypeString = "Unknown";
		break;
	}

	return evidenceTypeString;
}

std::string Utils::UnityStrToSysStr(const SDK::String& string)
{
	int length = string.Fields.StringLength;

	if (length <= 0)
	{
		return "UNKNOWN";
	}

	const uint16_t* chars = &string.Fields.FirstChar;

	std::wstring wideStr(chars, chars + length);
	std::string result;
	result.reserve(length);

	for (wchar_t wc : wideStr)
	{
		if (wc < 0x80)
			result.push_back(static_cast<char>(wc));
		else
		{
			if (wc < 0x800)
			{
				result.push_back(static_cast<char>(0xC0 | (wc >> 6)));
				result.push_back(static_cast<char>(0x80 | (wc & 0x3F)));
			}
			else
			{
				result.push_back(static_cast<char>(0xE0 | (wc >> 12)));
				result.push_back(static_cast<char>(0x80 | ((wc >> 6) & 0x3F)));
				result.push_back(static_cast<char>(0x80 | (wc & 0x3F)));
			}
		}
	}

	return result;
}

SDK::String* Utils::SysStrToUnityStr(const std::string& string)
{
	if (!il2cpp_initialize()) return nullptr;

	Il2CppDomain* domain = il2cpp_domain_get();
	if (!domain) return nullptr;

	il2cpp_thread_attach(domain);

	int len = MultiByteToWideChar(CP_UTF8, 0, string.c_str(), (int)string.size(), nullptr, 0);
	if (len == 0) return nullptr;

	std::wstring wstr(len, 0);
	MultiByteToWideChar(CP_UTF8, 0, string.c_str(), (int)string.size(), &wstr[0], len);

	Il2CppString* il2cppStr = il2cpp_string_new_utf16_wrap((const wchar_t*)wstr.c_str(), len);
	return reinterpret_cast<SDK::String*>(il2cppStr);
}

std::string Utils::GetPlayerName(const SDK::Player* player)
{
	if (!player)
		return {};

	try
	{
		const auto networkPlayerSpot = GetNetworkPlayerSpot(player);
		if (!networkPlayerSpot)
			return {};

		const auto& accountName = networkPlayerSpot->Fields.AccountName;
		if (!accountName)
			return {};

		return UnityStrToSysStr(*accountName);
	}
	catch (const std::exception& e)
	{
		LOG_ERROR("Failed to get player name: {}", e.what());
		return {};
	}
}

bool Utils::WTS(const SDK::Vector3& worldPos, SDK::Vector3& displayPos)
{
	RECT gameWindowRect;
	HWND gameWindowHandle = FindWindowA(nullptr, "Phasmophobia");
	GetWindowRect(gameWindowHandle, &gameWindowRect);

	const int windowHeight = gameWindowRect.bottom - gameWindowRect.top;
	SDK::Camera* playerCamera = GetLocalPlayer()->Fields.Camera;

	if (!playerCamera)
		return false;

	SDK::Transform* cameraTransform = SDK::Component_Get_Transform(
		reinterpret_cast<SDK::Component*>(playerCamera), nullptr);

	const SDK::Vector3 cameraLocation = SDK::Transform_Get_Position(cameraTransform, nullptr);
	const SDK::Vector3 cameraForwardDir = SDK::Transform_Get_Forward(cameraTransform, nullptr);

	SDK::Vector3 viewRay;
	viewRay.X = worldPos.X - cameraLocation.X;
	viewRay.Y = worldPos.Y - cameraLocation.Y;
	viewRay.Z = worldPos.Z - cameraLocation.Z;

	const float forwardDot = viewRay.X * cameraForwardDir.X +
		viewRay.Y * cameraForwardDir.Y +
		viewRay.Z * cameraForwardDir.Z;

	if (forwardDot <= 0.0f)
		return false;

	const SDK::Vector3 projectedCoords = SDK::Camera_WorldToScreenPoint(
		playerCamera, worldPos, nullptr);

	displayPos.X = projectedCoords.X;
	displayPos.Y = static_cast<float>(windowHeight) - projectedCoords.Y;
	displayPos.Z = projectedCoords.Z;

	return true;
}

SDK::Transform* Utils::GetPlayerTransformCamera(const SDK::Player* player)
{
	return SDK::Component_Get_Transform(reinterpret_cast<SDK::Component*>(player->Fields.Camera), nullptr);
}

SDK::Vector3 Utils::GetPosVec3(const SDK::Player* player)
{
	auto pos1 = GetPosVec3(GetPlayerTransformCamera(player));
	SDK::Vector3 newpos = { pos1.X, pos1.Y - 1.5f, pos1.Z };
	return newpos;
}

SDK::Vector3 Utils::GetPosVec3(const SDK::GhostAI* ghostAI)
{
	return GetPosVec3(ghostAI->Fields.huntingRaycastPoint);
}

SDK::Vector3 Utils::GetPosVec3(SDK::Component* component)
{
	return GetPosVec3(SDK::Component_Get_Transform(component, nullptr));
}

SDK::Vector3 Utils::GetPosVec3(SDK::Transform* transform)
{
	return SDK::Transform_Get_Position(transform, nullptr);
}

std::string Utils::GhostEnumToStr(SDK::EvidenceType evidenceType)
{
	switch (evidenceType)
	{
	case SDK::EvidenceType::emfSpot:
		return "EMF Spot";
	case SDK::EvidenceType::ouijaBoard:
		return "Ouija Board";
	case SDK::EvidenceType::fingerprint:
		return "Fingerprint";
	case SDK::EvidenceType::footstep:
		return "Footstep";
	case SDK::EvidenceType::DNA:
		return "";
	case SDK::EvidenceType::ghost:
		return "Ghost";
	case SDK::EvidenceType::deadBody:
		return "Dead Body";
	case SDK::EvidenceType::dirtyWater:
		return "Dirty Water";
	case SDK::EvidenceType::musicBox:
		return "Music Box";
	case SDK::EvidenceType::tarotCards:
		return "Tarot Cards";
	case SDK::EvidenceType::summoningCicle:
		return "Summoning Cicle";
	case SDK::EvidenceType::hauntedMirror:
		return "Haunted Mirror";
	case SDK::EvidenceType::voodooDoll:
		return "Voodoo Doll";
	case SDK::EvidenceType::ghostWriting:
		return "Ghost Writing";
	case SDK::EvidenceType::usedCrucifix:
		return "Used Crucifix";
	case SDK::EvidenceType::dotsGhost:
		return "DOTS Ghost";
	case SDK::EvidenceType::monkeyPaw:
		return "Monkey Paw";
	case SDK::EvidenceType::moonAlter:
		return "Moon Alter";
	case SDK::EvidenceType::ghostOrb:
		return "Ghost Orb";
	case SDK::EvidenceType::lightSource:
		return "Light Source";
	case SDK::EvidenceType::none:
		return "None";
	case SDK::EvidenceType::emfReader:
		return "EMF Reader";
	case SDK::EvidenceType::salt:
		return "Salt";
	case SDK::EvidenceType::freezingTemperature:
		return "Freezing Temperature";
	case SDK::EvidenceType::ghostSmoke:
		return "Ghost Smoke";
	case SDK::EvidenceType::camoGhost:
		return "Camo Ghost";
	case SDK::EvidenceType::paranormalSound:
		return "Paranormal Sound";
	case SDK::EvidenceType::spiritBox:
		return "Spirit Box";
	case SDK::EvidenceType::ghostHunt:
		return "Ghost Hunt";
	case SDK::EvidenceType::bansheeWail:
		return "Banshee Wail";
	case SDK::EvidenceType::teddyBear:
		return "Teddy Bear";
	case SDK::EvidenceType::spiritBoxBreath:
		return "Spirit Box Breath";
	case SDK::EvidenceType::motionSensor:
		return "Motion Sensor";
	case SDK::EvidenceType::shadowGhost:
		return "Shadow Ghost";
	case SDK::EvidenceType::ghostGroan:
		return "Ghost Groan";
	case SDK::EvidenceType::ghostLaugh:
		return "Ghost Laugh";
	case SDK::EvidenceType::ghostTalk:
		return "Ghost Talk";
	case SDK::EvidenceType::ghostWhisper:
		return "Ghost Whisper";
	case SDK::EvidenceType::obakeFingerprint:
		return "Obake Fingerprint";
	case SDK::EvidenceType::burningChapelCrucifix:
		return "Burning Chapel Crucifix";
	case SDK::EvidenceType::obakeShapeshift:
		return "Obake Shapeshift";
	default:
		return "Unknown";
	}
}

bool Utils::IsCursedItem(SDK::EvidenceType evidenceType)
{
	switch (evidenceType)
	{
	case SDK::EvidenceType::voodooDoll:
	case SDK::EvidenceType::tarotCards:
	case SDK::EvidenceType::ouijaBoard:
	case SDK::EvidenceType::hauntedMirror:
	case SDK::EvidenceType::musicBox:
	case SDK::EvidenceType::summoningCicle:
	case SDK::EvidenceType::monkeyPaw:
		return true;
	default:
		return false;
	}
}

SDK::LevelStats* Utils::GetLevelStats() 
{
	return SDK::LevelStats_get_Instance(nullptr);
}

double Utils::GetCheatUptimeSeconds()
{
	auto now = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(now - CheatInjectedTime);
	return duration.count();
}

float Utils::GetPlayerSanity(SDK::Player* player)
{
	return player->Fields.PlayerSanity->Fields.insanity;
}

bool Utils::IsLocalMasterClient()
{
	return SDK::PhotonNetwork_Get_IsMasterClient(nullptr);
}

void Utils::TpPlayerToVec3(SDK::Player* player, const SDK::Vector3& position)
{
	SDK::Player_Teleport(player, position, nullptr);
}

void Utils::TpPlayerToPlayer(SDK::Player* player, const SDK::Player* twoplayer)
{
	TpPlayerToVec3(player, GetPosVec3(twoplayer));
}

SDK::LevelValues* Utils::GetLevelValues()
{
	return SDK::LevelValues_get_Instance(nullptr);
}

SDK::Map* Utils::GetMap()
{
	return SDK::LevelValues_get_map(GetLevelValues(), nullptr);
}

std::string Utils::GetActiveSceneName()
{
	SDK::Scene scene = SDK::SceneManager_GetActiveScene(nullptr);
	SDK::String* namePtr = SDK::Scene_get_name(&scene, nullptr);
	if (!namePtr)
		return "UNKNOWN";
	return UnityStrToSysStr(*namePtr);
}

SDK::GameObject* Utils::FindObjectByName(std::string name)
{
	auto unityStrName = SysStrToUnityStr(name);
	return SDK::GameObject_Find(unityStrName, nullptr);
}

SDK::ObjectArray* Utils::FindObjectsByName()
{
	auto* goType = SDK::System_Type_GetType(SysStrToUnityStr("UnityEngine.GameObject"), nullptr);
	if (!goType) return nullptr;

	auto* all = SDK::Resources_FindObjectsOfTypeAll(goType, nullptr);
	if (!all) return nullptr;

	return all;
}

SDK::StoreItemInfo* Utils::GetStoreItemInfo()
{
	auto* list = FindObjectsByName();
	if (!list) return nullptr;

	for (uint32_t i = 0; i < 65535; i++)
	{
		auto raw = list->Vector[i];
		if (!raw) continue;

		auto* go = reinterpret_cast<SDK::GameObject*>(raw);

		auto* nameUnity = SDK::Object_Get_Name(reinterpret_cast<SDK::Object*>(go), nullptr);
		if (!nameUnity) continue;

		auto name = UnityStrToSysStr(*nameUnity);
		if (name != "Inspect Panel")
			continue;

		auto comp = SDK::GameObject_GetComponentByName(
			go,
			SysStrToUnityStr("StoreItemInfo"),
			nullptr
		);

		if (comp)
			return reinterpret_cast<SDK::StoreItemInfo*>(comp);
	}

	return nullptr;
}
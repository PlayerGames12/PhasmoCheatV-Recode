#include "soundboard.h"

using namespace PhasmoCheatV::Features::Map;

SoundBoard::SoundBoard() : FeatureCore(LANG("SoundBoard_Header"), TYPE_MAP) {}

void SoundBoard::OnMenuRender()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

	bool enabled = IsActive();
	if (ImGui::Checkbox(LANG("EnableSounBoard"), &enabled))
	{
		SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
		enabled ? OnActivate() : OnDeactivate();
	}

	if (!enabled)
	{
		ImGui::PopStyleVar();
		return;
	}

	BButton(LANG("LockSound"), "LockSound_sb", [this]() { // this is bad code
		pLockSound();
		});

	ImGui::SameLine();

	BButton(LANG("HuntingCloseDoorSound"), "HuntingCloseDoorSound_sb", [this]() {
		pHuntingCloseDoorSound();
		});

	BButton(LANG("SlamNoiseSound"), "SlamNoiseSound_sb", [this]() {
		pSlamNoiseSound();
		});

	ImGui::SameLine();

	BButton(LANG("RattlingNoiseSound"), "RattlingNoiseSound_sb", [this]() {
		pRattlingNoiseSound();
		});
	
	BButton(LANG("StopTruckSound"), "StopTruckSound_sb", [this]() {
		pStopTruckSound();
		});

	ImGui::SameLine();

	BButton(LANG("StartTruckSound"), "StartTruckSound_sb", [this]() { // im lazy :)
		pStartTruckSound();
		});

	ImGui::PopStyleVar();
}

SDK::Door* SoundBoard::getNearestDoor()
{
	auto localPlayer = Utils::GetLocalPlayer();
	if (!localPlayer)
	{
		NOTIFY_ERROR_QUICK(LANG(""));
		return nullptr;
	}

	auto playerPos = Utils::GetPosVec3(localPlayer);

	if (!SDK::LevelController_sFields->instance)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return nullptr;
	}

	auto& levelFields = SDK::LevelController_sFields->instance->Fields;
	auto doors = levelFields.doors;
	auto exitDoors = levelFields.exitDoors;

	float lowDistance = FLT_MAX;
	SDK::Door* nearestDoor = nullptr;

	for (int32_t i = 0; i < exitDoors->MaxLength; i++)
	{
		auto door = exitDoors->Vector[i];
		if (!door)
			continue;

		auto tr = SDK::Component_Get_Transform(reinterpret_cast<SDK::Component*>(door), nullptr);
		if (!tr)
			continue;

		auto doorPos = SDK::Transform_Get_Position(tr, nullptr);
		auto distance = Utils::Distance(playerPos, doorPos);
		
		if (distance < lowDistance)
		{
			lowDistance = distance;
			nearestDoor = door;
		}
	}

	for (int32_t i = 0; i < doors->MaxLength; i++)
	{
		auto door = doors->Vector[i];
		if (!door)
			continue;

		auto tr = SDK::Component_Get_Transform(reinterpret_cast<SDK::Component*>(door), nullptr);
		if (!tr)
			continue;

		auto doorPos = SDK::Transform_Get_Position(tr, nullptr);
		auto distance = Utils::Distance(playerPos, doorPos);

		if (distance < lowDistance)
		{
			lowDistance = distance;
			nearestDoor = door;
		}
	}

	return nearestDoor;
}

void SoundBoard::pLockSound()
{
	auto door = getNearestDoor();
	if (!door)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return;
	}

	auto photonView = door->Fields.photonView;
	if (!photonView)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return;
	}

	SDK::PhotonView_RPC(photonView, Utils::SysStrToUnityStr("NetworkedPlayLockSound"), SDK::RpcTarget::All, nullptr, nullptr);
}

void SoundBoard::pHuntingCloseDoorSound()
{
	auto door = getNearestDoor();
	if (!door)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return;
	}

	auto photonView = door->Fields.photonView;
	if (!photonView)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return;
	}

	bool isMaster = SDK::PhotonNetwork_Get_IsMasterClient(nullptr);
	if (!isMaster)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedMustBeHost"));
		return;
	}

	auto levelValues = SDK::LevelValues_get_Instance(nullptr);
	if (!levelValues)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return;
	}

	auto diff = levelValues->Fields.currentDifficulty;
	if (!diff)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return;
	}

	bool ghostFriendly = diff->Fields.friendlyGhost;
	if (ghostFriendly)
	{
		NOTIFY_ERROR_QUICK(LANG("FriendlyGhostLol"));
		return;
	}

	SDK::PhotonView_RPC(photonView, Utils::SysStrToUnityStr("HuntingCloseDoorNetworked"), SDK::RpcTarget::All, nullptr, nullptr);
}

void SoundBoard::pRattlingNoiseSound()
{
	auto door = getNearestDoor();
	if (!door)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return;
	}

	auto photonView = door->Fields.photonView;
	if (!photonView)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return;
	}

	bool isMaster = SDK::PhotonNetwork_Get_IsMasterClient(nullptr);
	if (!isMaster)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedMustBeHost"));
		return;
	}

	int32_t soundIndex = 1;

	auto intClass = il2cpp_get_class("mscorlib", "System", "Int32");
	if (!intClass)
		return;

	void* boxedInt = il2cpp_value_box(intClass, &soundIndex);
	if (!boxedInt)
		return;

	std::vector<void*> params{ boxedInt };

	auto parameters = Utils::VectorToIl2CppArray<void*>(
		params,
		"mscorlib",
		"System",
		"Object");

	if (!parameters)
		return;

	SDK::PhotonView_RPC(photonView, Utils::SysStrToUnityStr("PlayDoorRattlingNoise"), SDK::RpcTarget::All, parameters, nullptr);
}

void SoundBoard::pSlamNoiseSound()
{
	auto door = getNearestDoor();
	if (!door)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return;
	}

	auto photonView = door->Fields.photonView;
	if (!photonView)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return;
	}

	bool isMaster = SDK::PhotonNetwork_Get_IsMasterClient(nullptr);
	if (!isMaster)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedMustBeHost"));
		return;
	}

	SDK::PhotonView_RPC(photonView, Utils::SysStrToUnityStr("PlayDoorSlamNoise"), SDK::RpcTarget::All, nullptr, nullptr);
}

void SoundBoard::pStopTruckSound()
{
	auto exitLevel = Utils::GetExitLevel();
	if (!exitLevel)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return;
	}

	auto gobj_exitLevel = SDK::Component_Get_GameObject(reinterpret_cast<SDK::Component*>(exitLevel), nullptr);
	if (!gobj_exitLevel)
	{

	}
	//! pvCache = nullptr
	//auto photonView = exitLevel->Fields.monoBehaviourPunFields.pvCache;

	auto type = SDK::System_Type_GetType(Utils::SysStrToUnityStr("Photon.Pun.PhotonView"), nullptr);
	auto photonView = reinterpret_cast<SDK::PhotonView*>(SDK::GameObject_GetComponent(gobj_exitLevel, type, nullptr));
	if (!photonView)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		LOG_ERROR("photonView is null.");
		return;
	}

	bool isMaster = SDK::PhotonNetwork_Get_IsMasterClient(nullptr);
	if (!isMaster)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedMustBeHost"));
		return;
	}

	SDK::PhotonView_RPC(photonView, Utils::SysStrToUnityStr("PlayTruckStopSound"), SDK::RpcTarget::All, nullptr, nullptr);
}

void SoundBoard::pStartTruckSound()
{
	auto exitLevel = Utils::GetExitLevel();
	if (!exitLevel)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		return;
	}

	auto gobj_exitLevel = SDK::Component_Get_GameObject(reinterpret_cast<SDK::Component*>(exitLevel), nullptr);
	if (!gobj_exitLevel)
	{

	}
	//! pvCache = nullptr
	//auto photonView = exitLevel->Fields.monoBehaviourPunFields.pvCache;

	auto type = SDK::System_Type_GetType(Utils::SysStrToUnityStr("Photon.Pun.PhotonView"), nullptr);
	auto photonView = reinterpret_cast<SDK::PhotonView*>(SDK::GameObject_GetComponent(gobj_exitLevel, type, nullptr));
	if (!photonView)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedToBeInGame"));
		LOG_ERROR("photonView is null.");
		return;
	}

	bool isMaster = SDK::PhotonNetwork_Get_IsMasterClient(nullptr);
	if (!isMaster)
	{
		NOTIFY_ERROR_QUICK(LANG("NeedMustBeHost"));
		return;
	}

	SDK::PhotonView_RPC(photonView, Utils::SysStrToUnityStr("PlayTruckStartUpSound"), SDK::RpcTarget::All, nullptr, nullptr);
}

// need check InteractEffects (sounds)
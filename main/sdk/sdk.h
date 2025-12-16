#pragma once
#include "il2cpp/il2cpp.h"
#include "../main/logging/logger.h" // For LOGS
#include "../mem/memory.h"

using namespace PhasmoCheatV;

// EXPAMPLE USE: DEC_MET(Behaviour_Set_Enabled, void(*)(Behaviour* behaviour, bool enabled, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Behaviour", "set_enabled", 1);
#define DEC_MET(NAME, TYPE, ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT) \
using NAME##_ptr = TYPE; \
inline NAME##_ptr NAME = reinterpret_cast<NAME##_ptr>(il2cpp_get_method_pointer(ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT));

#define DEC_ADDR(NAME, TYPE, MODULE, OFFSET) \
inline TYPE* NAME##_ptr = reinterpret_cast<TYPE*>(reinterpret_cast<uintptr_t>(GetModuleHandleA(MODULE)) + OFFSET); \
inline TYPE NAME##_rd() { return Memory::Read<TYPE>(NAME##_ptr); } \
inline void NAME##_wr(TYPE val) { Memory::Write<TYPE>(NAME##_ptr, val); }

namespace SDK
{
    inline bool Initialize()
    {
		LOG_INFO("Initializing IL2CPP SDK...");
		LOG_INFO("GameAssembly.dll base address: ", (GetModuleHandleA("GameAssembly.dll")));
        return il2cpp_initialize();
    }
}

#include "MethodInfo.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "String.h"
#include "MonoBehaviour.h"
#include "RaycastHit.h"
#include "Camera.h"
#include "System.h"
#include "PhotonMessageInfo.h"
#include "TextMeshProUGUI.h"
#include "Transform.h"
#include "Object.h"
#include "GameObject.h"
#include "Resources.h"
#include "Component.h"
#include "Rigidbody.h"
#include "Cursor.h"
#include "GhostEvidence.h"
#include "GhostTraits.h"
#include "GhostInfo.h"
#include "GhostModel.h"
#include "GhostAI.h"
#include "GhostActivity.h"
#include "ExitLevel.h"
#include "Player.h"
#include "Door.h"
#include "LevelRoom.h"
#include "PlayerSanity.h"
#include "PlayerStamina.h"
#include "Network.h"
#include "PhotonNetwork.h"
#include "PhotonView.h"
#include "Door.h"
#include "LightSwitch.h"
#include "FuseBox.h"
#include "GameController.h"
#include "LevelController.h"
#include "MapController.h"
#include "PauseMenuController.h"
#include "MediaValues.h"
#include "DNAEvidence.h"
#include "Evidence.h"
#include "EvidenceController.h"
#include "Light.h"
#include "LevelStats.h"
#include "LineRenderer.h"
#include "EMFData.h"
#include "PhotonObjectInteract.h"
#include "MouseLook.h"
#include "PhysicsCharacterController.h"
#include "FirstPersonController.h"
#include "CursedItemsController.h"
#include "CursedItem.h"
#include "TarotCards.h"
#include "TarotCard.h"
#include "Time.h"
#include "ServerManager.h"
#include "ObjectiveManager.h"
#include "Difficulty.h"
#include "Map.h"
#include "LevelValues.h"
#include "Key.h"
#include "SceneManager.h"
#include "SaltSpot.h"
#include "SaltShaker.h"
#include "LevelSelectionManager.h"
#include "StoreItem.h"
#include "ItemInfo.h"
#include "StoreItemInfo.h"
#include "Application.h"
#include "JournalController.h"
#include "FallTeleportBox.h"
#include "JackInTheBox.h"
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

// Thanks Evelien. Thanks to Maxim for editing the macro. 
// I'm not going to explain how to search for signatures. Look for Signature maker and use it.
#define DECLARE_PATTERN_POINTER(NAME, TYPE, MODULE, SECTION, PATTERN) \
using NAME##_t = TYPE; \
inline NAME##_t NAME##_ptr = nullptr; \
inline bool NAME##_initialized = false; \
inline void Init_##NAME() { \
    if (NAME##_initialized) return; \
    NAME##_initialized = true; \
    const auto moduleHandle = GetModuleHandleW(MODULE); \
    if (!moduleHandle) return; \
    NAME##_ptr = reinterpret_cast<NAME##_t>(Memory::FindPatternInSection(moduleHandle, SECTION, PATTERN)); \
} \
inline NAME##_t Get_##NAME() { \
    if (!NAME##_initialized) Init_##NAME(); \
    return NAME##_ptr; \
} \
inline auto& NAME = *reinterpret_cast<NAME##_t*>(&Get_##NAME);

// By ViniLog
#define DECLARE_PATTERN_POINTER_MORE(NAME, TYPE, MODULE, SECTION, PATTERN, COUNT)       \
using NAME##_t = TYPE;                                                                 \
inline std::vector<NAME##_t> NAME##_ptrs;                                             \
inline bool NAME##_initialized = false;                                               \
inline void Init_##NAME() {                                                            \
    if (NAME##_initialized) return;                                                    \
    NAME##_initialized = true;                                                         \
    const auto moduleHandle = GetModuleHandleW(MODULE);                               \
    if (!moduleHandle) return;                                                         \
    NAME##_ptrs.clear();                                                               \
    uintptr_t lastAddr = 0;                                                            \
    size_t foundCount = 0;                                                             \
    while (foundCount < (COUNT)) {                                                     \
        uintptr_t addr = Memory::FindPatternInSection_more(moduleHandle, SECTION, PATTERN, lastAddr + 1); \
        if (!addr || addr <= lastAddr) break;                                         \
        NAME##_ptrs.push_back(reinterpret_cast<NAME##_t>(addr));                       \
        lastAddr = addr;                                                               \
        foundCount++;                                                                  \
    }                                                                                  \
}                                                                                      \
inline const std::vector<NAME##_t>& Get_##NAME##_All() {                               \
    if (!NAME##_initialized) Init_##NAME();                                            \
    return NAME##_ptrs;                                                                 \
}

// By ViniLog
#define DECLARE_PATTERN_INSTR(NAME, MODULE, SECTION, PATTERN)                    \
inline uintptr_t NAME##_addr = 0;                                                 \
inline bool NAME##_initialized = false;                                           \
inline uint8_t NAME##_originalBytes[5] = {0};                                     \
inline void Init_##NAME() {                                                       \
    if (NAME##_initialized) return;                                               \
    NAME##_initialized = true;                                                    \
    const auto hMod = GetModuleHandleW(MODULE);                                   \
    if (!hMod) return;                                                            \
    NAME##_addr = Memory::FindPatternInSection(hMod, SECTION, PATTERN);           \
    if (NAME##_addr) {                                                            \
        memcpy(NAME##_originalBytes, (void*)NAME##_addr, 5);                      \
    }                                                                             \
}                                                                                \
inline void NAME##_off() {                                                        \
    if (!NAME##_initialized) Init_##NAME();                                       \
    if (!NAME##_addr) return;                                                     \
    DWORD old;                                                                    \
    VirtualProtect((LPVOID)NAME##_addr, 5, PAGE_EXECUTE_READWRITE, &old);         \
    memset((void*)NAME##_addr, 0x90, 5);                                          \
    VirtualProtect((LPVOID)NAME##_addr, 5, old, &old);                            \
}                                                                                \
inline void NAME##_on() {                                                         \
    if (!NAME##_initialized) Init_##NAME();                                       \
    if (!NAME##_addr) return;                                                     \
    DWORD old;                                                                    \
    VirtualProtect((LPVOID)NAME##_addr, 5, PAGE_EXECUTE_READWRITE, &old);         \
    memcpy((void*)NAME##_addr, NAME##_originalBytes, 5);                          \
    VirtualProtect((LPVOID)NAME##_addr, 5, old, &old);                            \
}

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
#include "LightningController.h"
#include "WeatherProfile.h"
#include "RandomWeather.h"
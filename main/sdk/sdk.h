#pragma once
#include "il2cpp/il2cpp.h"
#include "../main/logging/logger.h" // For LOGS
#include "../mem/memory.h"

using namespace PhasmoCheatV;

// old macro, not safe, can cause crashes if the method is called before initialization. Use the new one below instead.
//#define DEC_MET(NAME, TYPE, ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT) \
//using NAME##_ptr = TYPE; \
//inline NAME##_ptr NAME = reinterpret_cast<NAME##_ptr>(il2cpp_get_method_pointer(ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT));

// Thanks Evelien
template <typename FuncType>
struct SafeFuncPtr
{
    FuncType raw = nullptr;
    const char* name = "unknown";

    SafeFuncPtr() = default;

    explicit SafeFuncPtr(const char* n) : name(n) {}

    SafeFuncPtr& operator=(FuncType p)
    {
        raw = p;
        return *this;
    }

    SafeFuncPtr& operator=(std::nullptr_t)
    {
        raw = nullptr;
        return *this;
    }

    explicit operator bool() const { return raw != nullptr; }

    template <typename... Args>
    auto operator()(Args... args) const -> decltype(raw(args...))
    {
        using RetType = decltype(raw(args...));

        if (!raw)
        {
            LOG_ERROR("Null SDK function call:", name);
            if constexpr (!std::is_void_v<RetType>)
                return RetType{};
            else
                return;
        }

        __try
        {
            return raw(args...);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            LOG_ERROR("SEH exception in SDK call:", name);
            if constexpr (!std::is_void_v<RetType>)
                return RetType{};
        }
    }
};

// EXPAMPLE USE: DEC_MET(Behaviour_Set_Enabled, void(*)(Behaviour* behaviour, bool enabled, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Behaviour", "set_enabled", 1);
#define DEC_MET(NAME, TYPE, ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT) \
using NAME##_ptr = TYPE; \
inline SafeFuncPtr<NAME##_ptr> NAME{#NAME}; \
inline void Init_##NAME() { \
    NAME = reinterpret_cast<NAME##_ptr>(il2cpp_get_method_pointer(ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT)); \
} \
namespace { \
    struct NAME##_registrar { \
        NAME##_registrar() { \
            static bool initialized = false; \
            if (!initialized) { \
                initialized = true; \
                Init_##NAME(); \
            } \
        } \
    }; \
    static NAME##_registrar NAME##_reg; \
}

#define DEC_ADDR(NAME, TYPE, MODULE, OFFSET) \
inline TYPE* NAME##_ptr = reinterpret_cast<TYPE*>(reinterpret_cast<uintptr_t>(GetModuleHandleA(MODULE)) + OFFSET); \
inline TYPE NAME##_rd() { return Memory::Read<TYPE>(NAME##_ptr); } \
inline void NAME##_wr(TYPE val) { Memory::Write<TYPE>(NAME##_ptr, val); }

// by asthmaphobia and Evelien
#define DECLARE_FUNCTION_POINTER(NAME, TYPE, ADDRESS) \
using NAME = TYPE; \
inline NAME NAME##_ptr = reinterpret_cast<NAME>(BASE_ADDRESS + ADDRESS);

// Thanks Evelien. Thanks to Maxim for editing the macro. 
// I'm not going to explain how to search for signatures. Look for Signature maker and use it.
#define DECLARE_PATTERN_POINTER(NAME, TYPE, MODULE, SECTION, PATTERN) \
using NAME##_t = TYPE; \
inline NAME##_t NAME##_ptr = nullptr; \
inline NAME##_t NAME##_original = nullptr; \
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
inline NAME##_t& GetOriginal_##NAME() { \
    if (!NAME##_original) NAME##_original = Get_##NAME(); \
    return NAME##_original; \
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
#define DEC_PATTERN_INSTR(NAME, MODULE, SECTION, PATTERN)                    \
inline uintptr_t NAME##_addr = 0;                                             \
inline bool NAME##_initialized = false;                                       \
inline bool NAME##_is_replaced = false;                                       \
inline uint8_t NAME##_originalBytes[32] = {0};                                \
inline size_t NAME##_savedSize = 0;                                           \
                                                                              \
inline void Init_##NAME() {                                                   \
    if (NAME##_initialized) return;                                           \
    NAME##_initialized = true;                                                \
    const auto hMod = GetModuleHandleW(MODULE);                               \
    if (!hMod) return;                                                        \
    NAME##_addr = Memory::FindPatternInSection(hMod, SECTION, PATTERN);       \
}                                                                             \
                                                                              \
inline void NAME##_save(size_t size) {                                        \
    if (!NAME##_initialized) Init_##NAME();                                   \
    if (!NAME##_addr) return;                                                 \
                                                                              \
    if (NAME##_savedSize == 0) {                                              \
        memcpy(NAME##_originalBytes, (void*)NAME##_addr, size);               \
        NAME##_savedSize = size;                                              \
    }                                                                         \
}                                                                             \
                                                                              \
inline void NAME##_nop(size_t count) {                                        \
    if (!NAME##_initialized) Init_##NAME();                                   \
    if (!NAME##_addr) return;                                                 \
                                                                              \
    NAME##_save(count);                                                       \
                                                                              \
    DWORD old;                                                                \
    VirtualProtect((LPVOID)NAME##_addr, count, PAGE_EXECUTE_READWRITE, &old); \
                                                                              \
    memset((void*)NAME##_addr, 0x90, count);                                  \
                                                                              \
    VirtualProtect((LPVOID)NAME##_addr, count, old, &old);                    \
                                                                              \
    NAME##_is_replaced = true;                                                \
}                                                                             \
                                                                              \
inline void NAME##_edit(std::initializer_list<uint8_t> bytes, size_t start = 0) { \
    if (!NAME##_initialized) Init_##NAME();                                   \
    if (!NAME##_addr) return;                                                 \
                                                                              \
    size_t size = bytes.size();                                               \
    NAME##_save(start + size);                                                \
                                                                              \
    DWORD old;                                                                \
    VirtualProtect((LPVOID)(NAME##_addr + start), size, PAGE_EXECUTE_READWRITE, &old); \
                                                                              \
    size_t i = 0;                                                             \
    for (auto b : bytes)                                                      \
        *((uint8_t*)(NAME##_addr + start + i++)) = b;                         \
                                                                              \
    VirtualProtect((LPVOID)(NAME##_addr + start), size, old, &old);           \
                                                                              \
    NAME##_is_replaced = true;                                                \
}                                                                             \
                                                                              \
inline void NAME##_restore() {                                                \
    if (!NAME##_initialized) Init_##NAME();                                   \
    if (!NAME##_addr || NAME##_savedSize == 0) return;                        \
                                                                              \
    DWORD old;                                                                \
    VirtualProtect((LPVOID)NAME##_addr, NAME##_savedSize, PAGE_EXECUTE_READWRITE, &old); \
                                                                              \
    memcpy((void*)NAME##_addr, NAME##_originalBytes, NAME##_savedSize);       \
                                                                              \
    VirtualProtect((LPVOID)NAME##_addr, NAME##_savedSize, old, &old);         \
                                                                              \
    NAME##_savedSize = 0;                                                     \
    NAME##_is_replaced = false;                                               \
}

// created for cosmetics unlocker
#define DEC_MET_CALL(NAME, TYPE, ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT, CALL_OFFSET) \
using NAME##_ptr = TYPE; \
inline NAME##_ptr NAME = nullptr; \
\
inline uintptr_t NAME##_resolve() { \
    auto baseFn = reinterpret_cast<uintptr_t>( \
        il2cpp_get_method_pointer(ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT)); \
    \
    if (!baseFn) return 0; \
    \
    uintptr_t callAddr = baseFn + (CALL_OFFSET); \
    \
    /* E8 rel32 */ \
    int32_t rel = *reinterpret_cast<int32_t*>(callAddr + 1); \
    uintptr_t nextInst = callAddr + 5; \
    \
    return nextInst + rel; \
} \
\
inline void Init_##NAME() { \
    NAME = reinterpret_cast<NAME##_ptr>(NAME##_resolve()); \
} \
\
namespace { \
    struct NAME##_registrar { \
        NAME##_registrar() { \
            static bool initialized = false; \
            if (!initialized) { \
                initialized = true; \
                Init_##NAME(); \
            } \
        } \
    }; \
    static NAME##_registrar NAME##_reg; \
}

namespace SDK
{
    const auto BASE_ADDRESS = reinterpret_cast<uintptr_t>(GetModuleHandleW(L"GameAssembly.dll"));

    inline bool Initialize()
    {
		LOG_INFO("Initializing IL2CPP SDK...");
		LOG_INFO("GameAssembly.dll base address: ", (GetModuleHandleA("GameAssembly.dll")));
        return il2cpp_initialize();
    }
}

#include "MethodInfo.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "String.h"
#include "MonoBehaviour.h"
#include "RaycastHit.h"
#include "Camera.h"
#include "System.h"
#include "Collider.h"
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
#include "Animator.h"
#include "Render.h"
#include "GhostModel.h"
#include "GhostAI.h"
#include "GhostActivity.h"
#include "ExitLevel.h"
#include "Voice.h"
#include "LocalPlayer.h"
#include "Player.h"
#include "Door.h"
#include "LevelRoom.h"
#include "PlayerSanity.h"
#include "PlayerStamina.h"
#include "Network.h"
#include "PhotonNetwork.h"
#include "PhotonView.h"
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
#include "EMF.h"
#include "EMFData.h"
#include "PhotonObjectInteract.h"
#include "MouseLook.h"
#include "PhysicsCharacterController.h"
#include "FirstPersonController.h"
#include "LocalPCPlayer.h"
#include "CursedItemsController.h"
#include "CursedItem.h"
#include "TarotCards.h"
#include "TarotCard.h"
#include "Time.h"
#include "ServerManager.h"
#include "ObjectiveManager.h"
#include "Difficulty.h"
#include "Map.h"
#include "Contract.h"
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
#include "LightningController.h"
#include "WeatherProfile.h"
#include "RandomWeather.h"
#include "LiftButton.h"
#include "HandCamera.h"
#include "LayerMask.h"
#include "Thermometer.h"
#include "Graphic.h"
#include "RectTransform.h"
#include "Screen.h"
#include "Torch.h"
#include "Texture.h"
#include "Equipment.h"
#include "Font.h"
#include "ThreeStateButton.h"
#include "GhostButton.h"
#include "Physics.h"
#include "Candle.h"
#include "SummoningCircle.h"
#include "VoodooDollPin.h"
#include "Jackalope.h"
#include "EVPRecorder.h"
#include "SteamFriends.h"
#include "ScriptableRenderContext.h"
#include "Media.h"
#include "JournalMedia.h"
#include "Journal_PhotoPage.h"
#include "Button.h"
#include "RewardManager.h"
#include "SceneManagement.h"
#include "CosmeticUnlocker.h"
#include "AWDoll.h"
#include "AudioSource.h"
#include "AzureEffectsController.h"
#include "Shader.h"
#include "Material.h"
#include "RenderSettings.h"
#include "test.h"

using namespace PhasmoCheatV;

// It is necessary for testing from the game stream. Called in GhostAI_Update only if IsDebugging = true
void Test::TestFeatures1()
{
    if (!IsDebugging) return;
    if (!ForTestsFlag) return;

    ForTestsFlag = false;
    LOG_INFO("The test executed");

    try
    {
        auto* list = Utils::FindObjectsOfType("JackInTheBox");
        if (!list) throw std::runtime_error("list null");

        SDK::Vector3 lpvec3{};
        auto* localPlayer = Utils::GetLocalPlayer();
        if (!localPlayer) throw std::runtime_error("localPlayer null");
        lpvec3 = Utils::GetPosVec3(localPlayer);

        for (uint32_t i = 0; i < 65535; ++i)
        {
            auto* raw = list->Vector[i];
            if (!raw) continue;

            //auto* obj = reinterpret_cast<SDK::GameObject*>(raw);
            //if (!obj) continue;

            //SDK::Transform_Set_Position(
            //   SDK::GameObject_get_transform(obj, nullptr),
            //    lpvec3,
            //    nullptr
            //);

            //SDK::GameObject_SetActive(obj, true, nullptr);

            LOG_INFO(SDK::Object_Get_Name(raw, nullptr)
            );
        }
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("TestWinterEvent failed", e.what());
    }
}

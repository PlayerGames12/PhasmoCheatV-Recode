#include "../Includes.h"

void Hooks::hkSaltShaker_Update(SDK::SaltShaker* saltShaker, SDK::MethodInfo* methodInfo)
{
    LOG_CALL_UPDATE("Called SaltShaker_Update");

    if (CheatWork)
    {
        auto& list = InGame::saltShakers;
        if (std::find(list.begin(), list.end(), saltShaker) == list.end()) 
        {
            list.push_back(saltShaker);
            LOG_INFO("Added SaltShaker in list {}", saltShaker);
        }
    }

    SDK::SaltShaker_Update(saltShaker, methodInfo);
}

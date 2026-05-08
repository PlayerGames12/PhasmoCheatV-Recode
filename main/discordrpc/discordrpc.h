#pragma once
#include "../Includes.h"

namespace Discord
{
    void Initialize();
    void Shutdown();
    void UpdatePresence();
    void DiscordRPCStatusHandler();

    extern bool Enabled;
}
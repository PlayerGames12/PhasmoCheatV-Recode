#pragma once
#include "main/sdk/sdk.h"

namespace PhasmoCheatV::InGame
{
    inline SDK::GhostAI* ghostAI = nullptr;

    // Reset in-game pointers
    inline void Reset() {
        ghostAI = nullptr;
    }

}
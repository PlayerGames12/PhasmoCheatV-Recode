#include "test.h"

using namespace PhasmoCheatV;

// It is necessary for testing from the game stream. Called in GhostAI_Update only if IsDebugging = true
void Test::TestFeatures1()
{
    if (!IsDebugging) return;
    if (!ForTestsFlag) return;

    ForTestsFlag = false;
    LOG_INFO("The test executed");
}
 
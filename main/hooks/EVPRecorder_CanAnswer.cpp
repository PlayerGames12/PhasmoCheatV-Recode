#include "../Includes.h"
#include "../features/features_includes.h"

using namespace PhasmoCheatV;

bool Hooks::hkEVPRecorder_CanAnswer(SDK::EVPRecorder* recorder, SDK::MethodInfo* methodInfo)
{
    LOG_CALL("Called EVPRecorder_CanAnswer");

    const auto ghostAI = InGame::ghostAI;
    if (ghostAI)
    {
        const auto ghostInfo = ghostAI->Fields.GhostInfo;
        if (ghostInfo)
        {
            const auto evidenceList = ghostInfo->Fields.GhostTraits.GhostEvidenceList;
            if (evidenceList && evidenceList->Fields.Size > 0)
            {
                const auto items = evidenceList->Fields.Items->Vector;

                for (int i = 0; i < evidenceList->Fields.Size; ++i)
                {
                    const std::string name = Utils::GhostEnumToStr(items[i]);

                    if (name == "Spirit Box" && GET_ACTIVE(Misc, SpiritBoxAlwaysAnswer))
                        return true;
                }
            }
        }
    }

    const auto original = SDK::GetOriginal_EVPRecorder_CanAnswer();
    return original(recorder, methodInfo);
}
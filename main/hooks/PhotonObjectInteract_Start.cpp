#include "../Includes.h"

void Hooks::hkPhotonObjectInteract_Start(SDK::PhotonObjectInteract* obj, SDK::MethodInfo* info)
{
    LOG_CALL_UPDATE("Called PhotonObjectInteract_Start");

    InGame::photonInstances.push_back(obj);

    SDK::PhotonObjectInteract_Start(obj, info);
}

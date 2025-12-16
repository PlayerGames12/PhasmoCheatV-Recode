#pragma once
#include "sdk.h"

namespace SDK
{
    DEC_MET(Time_Get_DeltaTime, float(*)(MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Time", "get_deltaTime", 0);
    DEC_MET(Time_Get_Time, float(*)(MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Time", "get_time", 0);
}
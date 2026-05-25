#pragma once
#include "sdk.h"

namespace SDK
{
    DEC_MET(RenderSettings_set_fog, void(*)(bool value, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "set_fog", 1);
    DEC_MET(RenderSettings_set_fogDensity, void(*)(float value, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "set_fogDensity", 1);
    DEC_MET(RenderSettings_set_fogColor, void(*)(Color value, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "set_fogColor", 1);
    DEC_MET(RenderSettings_set_ambientLight, void(*)(Color value, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "set_ambientLight", 1);
    DEC_MET(RenderSettings_set_ambientSkyColor, void(*)(Color value, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "set_ambientSkyColor", 1);
    DEC_MET(RenderSettings_set_ambientEquatorColor, void(*)(Color value, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "set_ambientEquatorColor", 1);
    DEC_MET(RenderSettings_set_ambientGroundColor, void(*)(Color value, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "set_ambientGroundColor", 1);
    DEC_MET(RenderSettings_set_ambientIntensity, void(*)(float value, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "set_ambientIntensity", 1);
    DEC_MET(RenderSettings_set_ambientMode, void(*)(int value, MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "set_ambientMode", 1);

    DEC_MET(RenderSettings_get_fog, bool(*)(MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_fog", 0);
    DEC_MET(RenderSettings_get_fogDensity, float(*)(MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_fogDensity", 0);
    DEC_MET(RenderSettings_get_fogColor, Color(*)(MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_fogColor", 0);
    DEC_MET(RenderSettings_get_ambientLight, Color(*)(MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_ambientLight", 0);
    DEC_MET(RenderSettings_get_ambientSkyColor, Color(*)(MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_ambientSkyColor", 0);
    DEC_MET(RenderSettings_get_ambientEquatorColor, Color(*)(MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_ambientEquatorColor", 0);
    DEC_MET(RenderSettings_get_ambientGroundColor, Color(*)(MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_ambientGroundColor", 0);
    DEC_MET(RenderSettings_get_ambientIntensity, float(*)(MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_ambientIntensity", 0);
    DEC_MET(RenderSettings_get_ambientMode, int(*)(MethodInfo* method), "UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_ambientMode", 0);
}

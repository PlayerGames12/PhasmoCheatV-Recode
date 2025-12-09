#pragma once
#include "sdk.h"

namespace SDK
{
    enum class LightType : int 
    {
        Spot,
        Directional,
        Point,
        Area
    };

    enum class ShadowsType : int 
    {
        None,
        Hard,
        Soft
    };

    enum class RenderMode : int
    {
        Auto,
        ForcePixel,
        ForceVertex
    };

    struct Light;

    DEC_MET(Light_intensity_set, void(*)(Light* light, float value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light", "set_intensity", 1);
    DEC_MET(Light_type_set, void(*)(Light* light, LightType value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light", "set_type", 1);
    DEC_MET(Light_shadows_set, void(*)(Light* light, ShadowsType value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light", "set_shadows", 1);
    DEC_MET(Light_renderMode_set, void(*)(Light* light, RenderMode value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light", "set_renderMode", 1);
}
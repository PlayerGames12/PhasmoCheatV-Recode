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
    DEC_MET(Light_intensity_get, float(*)(Light* light, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light", "get_intensity", 0);
    DEC_MET(Light_color_set, void(*)(Light* light, Color value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light", "set_color", 1);
    DEC_MET(Light_color_get, Color(*)(Light* light, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light", "get_color", 0);
    DEC_MET(Light_type_set, void(*)(Light* light, LightType value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light", "set_type", 1);
    DEC_MET(Light_shadows_set, void(*)(Light* light, ShadowsType value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light", "set_shadows", 1);
    DEC_MET(Light_renderMode_set, void(*)(Light* light, RenderMode value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light", "set_renderMode", 1);
    DEC_MET(Light_range_set, void(*)(Light* light, float value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light", "set_range", 1);
}
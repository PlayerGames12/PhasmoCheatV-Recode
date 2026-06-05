#pragma once
#include "sdk.h"

namespace SDK
{
    struct Material;
    struct Texture;
    DEC_MET(Material_set_color, void(*)(Material* material, Color value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Material", "set_color", 1);
    DEC_MET(Material_SetColor, void(*)(Material* material, String* name, Color value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Material", "SetColor", 2);
    DEC_MET(Material_GetColor, Color(*)(Material* material, String* name, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Material", "GetColor", 1);
    DEC_MET(Material_SetFloat, void(*)(Material* material, String* name, float value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Material", "SetFloat", 2);
    DEC_MET(Material_get_color, Color(*)(Material* material, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Material", "get_color", 0);
    DEC_MET(Material_set_mainTexture, void(*)(Material* material, Texture* value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Material", "set_mainTexture", 1);
    DEC_MET(Material_get_name, String* (*)(Material* material, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Material", "get_name", 0);
    DEC_MET(Material_get_shader, Shader* (*)(Material* material, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Material", "get_shader", 0);
    DEC_MET(Material_set_shader, Shader* (*)(Material* material, Shader* shader, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Material", "set_shader", 1);
    DEC_MET(Material_EnableKeyword, Shader* (*)(Material* material, String* value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Material", "EnableKeyword", 1);
}

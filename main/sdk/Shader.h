#pragma once
#include "sdk.h"

namespace SDK
{
	struct Shader;

	DEC_MET(Shader_Find, Shader* (*)(String* str, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Shader", "Find", 1);
	DEC_MET(Shader_DisableKeyword, void(*)(String* keyword, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Shader", "DisableKeyword", 1);
	DEC_MET(Shader_EnableKeyword, void(*)(String* keyword, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Shader", "EnableKeyword", 1);
}
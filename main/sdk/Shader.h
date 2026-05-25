#pragma once
#include "sdk.h"

namespace SDK
{
	struct Shader;

	DEC_MET(Shader_Find, Shader* (*)(String* str, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Shader", "Find", 1);
}
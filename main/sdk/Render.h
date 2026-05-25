#pragma once
#include "sdk.h"

namespace SDK
{
	struct Render;
	struct Material;

	DEC_MET(Render_get_enabled, bool(*)(Render* render, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Renderer", "get_enabled", 0);
	DEC_MET(Render_get_material, Material* (*)(Render* render, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Renderer", "get_material", 0);
	DEC_MET(Render_get_sharedMaterial, Material* (*)(Render* render, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Renderer", "get_sharedMaterial", 0);
	DEC_MET(Render_set_material, void(*)(Render* render, Material* value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Renderer", "set_material", 1);
	DEC_MET(Render_set_sharedMaterial, void(*)(Render* render, Material* value, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Renderer", "set_sharedMaterial", 1);
}
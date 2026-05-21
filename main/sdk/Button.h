#pragma once
#include "sdk.h"

namespace SDK
{
	struct Button;

	DEC_MET(Button_Press, void(*)(Button* button, MethodInfo* methodInfo), "UnityEngine.UI", "UnityEngine.UI", "Button", "Press", 0);
}
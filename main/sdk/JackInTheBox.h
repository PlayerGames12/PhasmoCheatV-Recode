#pragma once
#include "sdk.h"

namespace SDK
{
	struct JackInTheBox;

	DEC_MET(JackInTheBox_UseNetworked, void(*)(JackInTheBox* jackInTheBox, MethodInfo* methodInfo), "Assembly-CSharp", "", "JackInTheBox", "UseNetworked", 0);
}
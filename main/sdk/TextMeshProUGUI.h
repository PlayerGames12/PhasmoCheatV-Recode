#pragma once
#include "sdk.h"

namespace SDK
{
	struct TextMeshProUGUI;
	struct TMP_Text;

	DEC_MET(TMP_Text_set_text, void(*)(TMP_Text* tmp_Text, String* value, MethodInfo* methodInfo), "Unity.TextMeshPro", "TMPro", "TMP_Text", "set_text", 1);
	DEC_MET(TMP_Text_get_text, String* (*)(TMP_Text* tmp_Text, MethodInfo* methodInfo), "Unity.TextMeshPro", "TMPro", "TMP_Text", "get_text", 0);
}
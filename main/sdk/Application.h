#pragma once
#include "sdk.h"

namespace SDK
{
	struct Application;

	enum LogType : int32_t
	{
		Error = 0,
		Assert = 1,
		Warning = 2,
		Log = 3,
		Exception = 4
	};

	DEC_MET(Application_CallLogCallback, void(*)(String* logString, String* stackTrace, LogType type, bool invokedOnMainThread, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Application", "CallLogCallback", 4);
}

#include "../Includes.h"

void Hooks::hkApplication_CallLogCallback(SDK::String* logString, SDK::String* stackTrace, SDK::LogType type, bool invokedOnMainThread, SDK::MethodInfo* methodInfo)
{
	if (CheatWork && RedirectUnityLogs && IsDebugging)
	{
		std::string logMsg = Utils::UnityStrToSysStr(*logString);
		std::string stackMsg = Utils::UnityStrToSysStr(*stackTrace);

		if (type == SDK::LogType::Error || type == SDK::LogType::Exception)
		{
			LOG_UNITY_ERROR(logMsg);
			LOG_UNITY_ERROR(stackMsg);
		}
		else if (type == SDK::LogType::Warning)
		{
			LOG_UNITY_WARN(logMsg);
			LOG_UNITY_WARN(stackMsg);
		}
		else if (type == SDK::LogType::Log)
		{
			LOG_UNITY(logMsg);
			LOG_UNITY(stackMsg);
		}
	}

	SDK::Application_CallLogCallback(logString, stackTrace, type, invokedOnMainThread, methodInfo);
}
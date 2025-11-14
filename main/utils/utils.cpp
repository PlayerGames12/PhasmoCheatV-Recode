#include "utils.h"

using namespace PhasmoCheatV;

std::string Utils::GetPhasmoCheatVDirectory()
{
	return "C:\\PhasmoCheatV";
}

void Utils::CreatePhasmoCheatVDirectory()
{
	const std::string configDirectoryPath = GetPhasmoCheatVDirectory();
	if (std::filesystem::exists(configDirectoryPath))
		return;

	LOG_INFO("PhasmoCheatV directory not found, creating one.");
	std::filesystem::create_directory(configDirectoryPath);
}

std::string Utils::getKeyName(int keyCode)
{
	switch (keyCode)
	{
	case VK_INSERT: return "INSERT";
	case VK_DELETE: return "DELETE";
	case VK_HOME: return "HOME";
	case VK_END: return "END";
	case VK_PRIOR: return "PAGE UP";
	case VK_NEXT: return "PAGE DOWN";
	case VK_F1: return "F1";
	case VK_F2: return "F2";
	case VK_F3: return "F3";
	case VK_F4: return "F4";
	case VK_F5: return "F5";
	case VK_F6: return "F6";
	case VK_F7: return "F7";
	case VK_F8: return "F8";
	case VK_F9: return "F9";
	case VK_F10: return "F10";
	case VK_F11: return "F11";
	case VK_F12: return "F12";
	default:
		if (keyCode >= 'A' && keyCode <= 'Z')
			return std::string(1, (char)keyCode);
		else if (keyCode >= '0' && keyCode <= '9')
			return std::string(1, (char)keyCode);
		else
			return "Key " + std::to_string(keyCode);
	}
}

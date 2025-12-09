#include "customname.h"

using namespace PhasmoCheatV::Features::Players;

CustomName::CustomName() : FeatureCore("Custom name", TYPE_PLAYERS)
{
    DECLARE_CONFIG(GetConfigManager(), "Nickname", std::string, "PhasmoCheatV");
}

void CustomName::OnMenuRender()
{
    std::string nickname = CONFIG_STRING(GetConfigManager(), "Nickname");
    strcpy_s(Name_Buff, nickname.c_str());

    if (ImGui::InputText("##custname", Name_Buff, IM_ARRAYSIZE(Name_Buff)))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Nickname", std::string, Name_Buff);
    }

    ImGui::SameLine();
    if (ImGui::Button("Set name##custname"))
    {
        SDK::PhotonNetwork_Set_NickName(Utils::SysStrToUnityStr(std::string(Name_Buff)), nullptr);
    }
}
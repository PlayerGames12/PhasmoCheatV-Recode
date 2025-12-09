#include "saltmodifier.h"

using namespace PhasmoCheatV::Features::Map;

SaltModifier::SaltModifier() : FeatureCore("Salt Modifier (ONLY YOU)", TYPE_MAP)
{
    DECLARE_CONFIG(GetConfigManager(), "InfinitySalt", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "NoSaltUsedGhost", bool, false);
}

void SaltModifier::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox("Enable Salt Modifier", &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled)
    {
        bool infSalt = CONFIG_BOOL(GetConfigManager(), "InfinitySalt");
        bool noSaltUsedGhost = CONFIG_BOOL(GetConfigManager(), "NoSaltUsedGhost");

        if (ImGui::Checkbox("Infinity Salt", &infSalt))
            SET_CONFIG_VALUE(GetConfigManager(), "InfinitySalt", bool, infSalt);

        if (ImGui::Checkbox("Ghost doesn't use salt", &noSaltUsedGhost))
            SET_CONFIG_VALUE(GetConfigManager(), "NoSaltUsedGhost", bool, noSaltUsedGhost);

        if (ImGui::Button("Reset all salt"))
        {
            SDK::String* saltSpotTypeName = Utils::SysStrToUnityStr("SaltSpot");
            SDK::Type* saltSpotType = SDK::System_Type_GetType(saltSpotTypeName, nullptr);
            SDK::ObjectArray* saltSpots = SDK::Object_FindObjectsOfType(saltSpotType, nullptr);
            if (!saltSpots) return;
            for (uint32_t i = 0; i < 65535; i++)
            {
                auto obj = saltSpots->Vector[i];
                if (!obj) break;
                SDK::SaltSpot* saltSpot = reinterpret_cast<SDK::SaltSpot*>(obj);
                bool used = saltSpot->Fields.used;
                SDK::GameObject_SetActive(saltSpot->Fields.flatSalt, false, nullptr);
                SDK::GameObject_SetActive(saltSpot->Fields.normalSalt, true, nullptr);
                saltSpot->Fields.used = false;
            }
        }
        
        ImGui::SameLine();

        if (ImGui::Button("Use all salt"))
        {
            SDK::String* saltSpotTypeName = Utils::SysStrToUnityStr("SaltSpot");
            SDK::Type* saltSpotType = SDK::System_Type_GetType(saltSpotTypeName, nullptr);
            SDK::ObjectArray* saltSpots = SDK::Object_FindObjectsOfType(saltSpotType, nullptr);
            if (!saltSpots) return;
            for (uint32_t i = 0; i < 65535; i++)
            {
                auto obj = saltSpots->Vector[i];
                if (!obj) break;
                SDK::SaltSpot* saltSpot = reinterpret_cast<SDK::SaltSpot*>(obj);
                bool used = saltSpot->Fields.used;
                SDK::GameObject_SetActive(saltSpot->Fields.flatSalt, true, nullptr);
                SDK::GameObject_SetActive(saltSpot->Fields.normalSalt, false, nullptr);
                saltSpot->Fields.used = true;
            }
        }
    }

    ImGui::PopStyleVar();
}

void SaltModifier::SaltModifierMain()
{
    if (!IsActive()) return;
    if (CONFIG_BOOL(GetConfigManager(), "InfinitySalt"))
    {
        if (InGame::saltShakers.empty())
            return;

        for (auto* saltShaker : InGame::saltShakers)
        {
            saltShaker->Fields.uses = 3;
        }
    }
}

void SaltModifier::SaltModifierMainNoUseGhost(SDK::SaltSpot* saltSpot, void* photon, SDK::MethodInfo* methodInfo)
{
    if (IsActive() && CONFIG_BOOL(GetConfigManager(), "NoSaltUsedGhost"))
        return;
    SDK::SaltSpot_SyncSalt(saltSpot, photon, methodInfo);
}

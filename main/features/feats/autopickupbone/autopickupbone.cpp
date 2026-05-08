#include "autopickupbone.h"

using namespace PhasmoCheatV::Features::Map;

AutoPickupBone::AutoPickupBone() : FeatureCore(LANG("Autopickupbone_Header"), TYPE_MAP) {}

void AutoPickupBone::OnMenuRender()
{
    bool enabled = IsActive();
    if (ImGui::Checkbox(LANG("AutoPickupBoneEnable"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }
}
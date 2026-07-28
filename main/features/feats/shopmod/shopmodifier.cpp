#include "shopmodifier.h"

using namespace PhasmoCheatV::Features::Misc;

namespace
{
    void DisableTutorialByName(const char* tutorialName)
    {
        auto* tutorial = Utils::FindObjectByName(tutorialName);
        if (!tutorial)
            return;

        SDK::GameObject_SetActive(tutorial, false, nullptr);
    }
}

ShopModifier::ShopModifier() : FeatureCore(LANG("ShopModifier_Header"), TYPE_MISC)
{
    DECLARE_CONFIG(GetConfigManager(), "SkipShopTutorials", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "CustomCost", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "CustomCount", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "CustomUpgradeCost", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "CustomRequiredLevel", bool, false);
    DECLARE_CONFIG(GetConfigManager(), "CustomCostValue", int32_t, 100);
    DECLARE_CONFIG(GetConfigManager(), "CustomCountValue", int32_t, 100);
    DECLARE_CONFIG(GetConfigManager(), "CustomUpgradeCostValue", int32_t, 100);
    DECLARE_CONFIG(GetConfigManager(), "CustomRequiredLevelValue", int32_t, 1);
}

void ShopModifier::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    bool skipShopTutorials = CONFIG_BOOL(GetConfigManager(), "SkipShopTutorials");
    bool customCost = CONFIG_BOOL(GetConfigManager(), "CustomCost");
    bool customCount = CONFIG_BOOL(GetConfigManager(), "CustomCount");
    bool customUpgradeCost = CONFIG_BOOL(GetConfigManager(), "CustomUpgradeCost");
    bool customRequiredLevel = CONFIG_BOOL(GetConfigManager(), "CustomRequiredLevel");

    int32_t customCostValue = CONFIG_INT(GetConfigManager(), "CustomCostValue");
    int32_t customCountValue = CONFIG_INT(GetConfigManager(), "CustomCountValue");
    int32_t customUpgradeCostValue = CONFIG_INT(GetConfigManager(), "CustomUpgradeCostValue");
    int32_t customRequiredLevelValue = CONFIG_INT(GetConfigManager(), "CustomRequiredLevelValue");

    if (ImGui::Checkbox(LANG("EnableShopModifier"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled)
    {
        if (ImGui::Checkbox(LANG("SkipShopTutorials"), &skipShopTutorials))
            SET_CONFIG_VALUE(GetConfigManager(), "SkipShopTutorials", bool, skipShopTutorials);

        if (ImGui::Checkbox(LANG("CustomCost"), &customCost))
            SET_CONFIG_VALUE(GetConfigManager(), "CustomCost", bool, customCost);

        if (customCost)
        {
            if (ImGui::SliderInt(LANG("CustomCostValue"), &customCostValue, 0, 1000000))
                SET_CONFIG_VALUE(GetConfigManager(), "CustomCostValue", int32_t, customCostValue);
        }

        if (ImGui::Checkbox(LANG("CustomCount"), &customCount))
            SET_CONFIG_VALUE(GetConfigManager(), "CustomCount", bool, customCount);

        if (customCount)
        {
            if (ImGui::SliderInt(LANG("CustomCountValue"), &customCountValue, 0, 999))
                SET_CONFIG_VALUE(GetConfigManager(), "CustomCountValue", int32_t, customCountValue);
        }

        if (ImGui::Checkbox(LANG("CustomUpgradeCost"), &customUpgradeCost))
            SET_CONFIG_VALUE(GetConfigManager(), "CustomUpgradeCost", bool, customUpgradeCost);

        if (customUpgradeCost)
        {
            if (ImGui::SliderInt(LANG("CustomUpgradeCostValue"), &customUpgradeCostValue, 0, 1000000))
                SET_CONFIG_VALUE(GetConfigManager(), "CustomUpgradeCostValue", int32_t, customUpgradeCostValue);
        }

        if (ImGui::Checkbox(LANG("CustomRequiredLevel"), &customRequiredLevel))
            SET_CONFIG_VALUE(GetConfigManager(), "CustomRequiredLevel", bool, customRequiredLevel);

        if (customRequiredLevel)
        {
            if (ImGui::SliderInt(LANG("CustomRequiredLevelValue"), &customRequiredLevelValue, 0, 999))
                SET_CONFIG_VALUE(GetConfigManager(), "CustomRequiredLevelValue", int32_t, customRequiredLevelValue);
        }
    }

    ImGui::PopStyleVar();
}

void ShopModifier::OnActivate()
{
    lastUpdateTime = 0.0f;
    lastTutorialLookupTime = 0.0f;
}

void ShopModifier::OnDeactivate()
{
    lastUpdateTime = 0.0f;
    lastTutorialLookupTime = 0.0f;
}

void ShopModifier::OnRender()
{
    if (!IsActive())
        return;

    const float now = SDK::Time_Get_Time(nullptr);
    if (now <= 0.0f)
        return;

    // Run at a lower cadence to reduce lobby CPU overhead.
    if (lastUpdateTime > 0.0f && (now - lastUpdateTime) < 0.25f)
        return;

    lastUpdateTime = now;
    ShopModifierMain();
}

void ShopModifier::ShopModifierMain()
{
    if (!IsActive())
        return;

    if (Utils::GetGhostAI())
        return;

    const bool skipShopTutorials = CONFIG_BOOL(GetConfigManager(), "SkipShopTutorials");
    const bool customCost = CONFIG_BOOL(GetConfigManager(), "CustomCost");
    const bool customCount = CONFIG_BOOL(GetConfigManager(), "CustomCount");
    const bool customUpgradeCost = CONFIG_BOOL(GetConfigManager(), "CustomUpgradeCost");
    const bool customRequiredLevel = CONFIG_BOOL(GetConfigManager(), "CustomRequiredLevel");

    if (!skipShopTutorials && !customCost && !customCount && !customUpgradeCost && !customRequiredLevel)
        return;

    if (skipShopTutorials)
    {
        const float now = SDK::Time_Get_Time(nullptr);
        if (now > 0.0f && (lastTutorialLookupTime <= 0.0f || (now - lastTutorialLookupTime) >= 1.0f))
        {
            lastTutorialLookupTime = now;
            DisableTutorialByName("Shop Tutorial");
            DisableTutorialByName("Storage Tutorial");
            DisableTutorialByName("Loadout Tutorial");
        }
    }

    if (!customCost && !customCount && !customUpgradeCost && !customRequiredLevel)
        return;

    auto* storeInfo = Utils::GetStoreItemInfo();

    if (!storeInfo)
        return;

    auto* item = storeInfo->Fields.ItemInfoFields.item;
    if (!item)
        return;

    if (customCost)
    {
        const int value = CONFIG_INT(GetConfigManager(), "CustomCostValue");
        if (item->Fields.cost != value)
            item->Fields.cost = value;
    }

    if (customCount)
    {
        const int value = CONFIG_INT(GetConfigManager(), "CustomCountValue");
        if (item->Fields.m_amountOwned != value)
            item->Fields.m_amountOwned = value;
    }

    if (customUpgradeCost)
    {
        const int value = CONFIG_INT(GetConfigManager(), "CustomUpgradeCostValue");
        if (item->Fields.upgradeCost != value)
            item->Fields.upgradeCost = value;
    }

    if (customRequiredLevel)
    {
        const int value = CONFIG_INT(GetConfigManager(), "CustomRequiredLevelValue");
        if (item->Fields.requiredLevel != value)
            item->Fields.requiredLevel = value;
    }
}

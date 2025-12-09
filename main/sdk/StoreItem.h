#pragma once
#include "../Includes.h"

namespace SDK
{
    struct StoreItemFields
    {
        char pad_000[8]; // ScriptableObject Fields
        int32_t equipmentType;
        int32_t tier;
        void* itemName;
        void* descriptionID;
        void* loreID;
        int32_t cost;
        int32_t upgradeCost;
        int32_t requiredLevel;
        int32_t defaultAmount;
        int32_t maxAmount;
        bool isConsumable;
        void* icon;
        void* blueprintSprite;
        void* unlockSprite;
        void* features;
        int32_t m_amountOwned;
    };

	struct StoreItem
	{
		void* Clazz;
		void* Monitor;
		StoreItemFields Fields;
	};
}
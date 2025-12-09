#pragma once
#include "../Includes.h"

namespace SDK
{
    struct ItemInfoFields
    {
        MonoBehaviourFields MonoBehaviourFields;
        void* nameTextLocaliser;
        void* tierText;
        void* costText;
        void* ownedText;
        void* equipmentImage;
        void* descriptionTextLocaliser;
        void* loreTextLocaliser;
        void* allEquipmentProperties;
        void* overlayObject;
        void* lockedObject;
        void* upgradeAvailableObject;
        void* requirementsText;
        void* hoverInfo;
        void* hoverInfoText;
        StoreItem* item;
        void* equipment;
        void* equipmentTier;
    };

	struct ItemInfo
	{
		void* Clazz;
		void* Monitor;
		ItemInfoFields Fields;
	};
}
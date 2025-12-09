#pragma once
#include "sdk.h"

namespace SDK
{
    struct MouseLookFields
    {
        float XSensitivity;
        float YSensitivity;
        bool clampVerticalRotation;
        float MinimumX;
        float MaximumX;
        bool smooth;
        float smoothTime;
        bool lockCursor;
        void* sensor;
        char pad_0004[0x48];
        Quaternion m_CharacterTargetRot;
        Quaternion m_CameraTargetRot;
    };

	struct MouseLook
	{
		void* Clazz;
		void* Monitor;
		MouseLookFields Fields;
	};
}

#pragma once
#include "sdk.h"

namespace SDK
{
	struct Quaternion
	{
		float X;
		float Y;
		float Z;
		float W;
	};

	inline Quaternion identityQuaternion = { 0, 0, 0, 0 };
}

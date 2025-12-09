#pragma once
#include "sdk.h"

namespace SDK
{
	struct RaycastHit
	{
		Vector3 Point;
		Vector3 Normal;
		uint32_t FaceID;
		float Distance;
		Vector2 UV;
		int Collider;
	};
}

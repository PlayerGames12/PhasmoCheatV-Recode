#pragma once
#include "sdk.h"

namespace SDK
{
	enum class GhostEvidence : int32_t
	{
		None,
		EMF,
		SpiritBox,
		Ultraviolet,
		GhostOrb,
		GhostWritingBook,
		Temperature,
		DotsProjector
	};

	struct GhostEvidenceArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds;
		void* MaxLength;
		GhostEvidence Vector[65535];
	};

	struct __declspec(align(8)) ListGhostEvidenceFields
	{
		GhostEvidenceArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot;
	};

	struct ListGhostEvidence
	{
		void* Clazz;
		void* Monitor;
		ListGhostEvidenceFields Fields;
	};
}

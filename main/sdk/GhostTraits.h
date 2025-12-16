#pragma once
#include "sdk.h"

namespace SDK
{
	enum class GhostType : int32_t
	{
		Spirit,
		Wraith,
		Phantom,
		Poltergeist,
		Banshee,
		Jinn,
		Mare,
		Revenant,
		Shade,
		Demon,
		Yurei,
		Oni,
		Yokai,
		Hantu,
		Goryo,
		Myling,
		Onryo,
		TheTwins,
		Raiju,
		Obake,
		Mimic,
		Moroi,
		Deogen,
		Thaye,
		None
	};

	struct GhostTraits
	{
		GhostType GhostType_;
		GhostType MimicType;
		ListGhostEvidence* GhostEvidenceList;
		ListGhostEvidence* FakeEvidenceList;
		int32_t GhostAge;
		bool IsMale;
		String* Name;
		int32_t FirstNameId;
		int32_t LastNameId;
		bool IsShy;
		int32_t DeathLength;
		int32_t FavouriteRoomId;
		bool IsActive;
	};
}

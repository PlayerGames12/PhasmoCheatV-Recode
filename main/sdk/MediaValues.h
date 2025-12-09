#pragma once
#include "sdk.h"

namespace SDK
{
	enum class EvidenceType;

	enum class EvidenceQualityType : int32_t
	{
		None,
		Duplicate,
		Unique
	};

	enum class TierList : int32_t
	{
		One,
		Two,
		Three
	};

	struct MediaValuesFields
	{
		char pad_000[8]; // ScriptableObject
		EvidenceType EvidenceType;
		void* EMFInteractionType;
		void* capturableMedia;
		String* localisedNameKey;
		String* LocalisedDescKey;
		int32_t uniqueValue;
		int32_t duplicateValue;
	};

	struct MediaValues
	{
		void* Clazz;
		void* Monitor;
		MediaValuesFields Fields;
	};

	DEC_MET(MediaValues_GetRewardAmount, int(*)(MediaValues* mediaValues, EvidenceQualityType qualityType, TierList mediaTier, MethodInfo* methodInfo), "Assembly-CSharp", "", "MediaValues", "GetRewardAmount", 2);
}

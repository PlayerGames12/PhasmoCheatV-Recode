#pragma once
#include "sdk.h"

namespace SDK
{
	struct EvidenceFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		MediaValues* MediaValues;
		bool Field1;
		bool ResetTakenPhotoOnEnable;
	};

	struct Evidence
	{
		void* Clazz;
		void* Monitor;
		EvidenceFields Fields;
	};

	struct EvidenceArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds;
		void* MaxLength;
		Evidence* Vector[65535];
	};

	struct __declspec(align(8)) ListEvidenceFields
	{
		EvidenceArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot;
	};

	struct ListEvidence
	{
		void* Clazz;
		void* Monitor;
		ListEvidenceFields Fields;
	};

	enum class EvidenceType : int32_t
	{
		emfSpot,
		ouijaBoard,
		fingerprint,
		footstep,
		DNA,
		ghost,
		deadBody,
		dirtyWater,
		musicBox,
		tarotCards,
		summoningCicle,
		hauntedMirror,
		voodooDoll,
		ghostWriting,
		usedCrucifix,
		dotsGhost,
		monkeyPaw,
		moonAlter,
		ghostOrb,
		lightSource,
		none,
		emfReader,
		salt,
		freezingTemperature,
		ghostSmoke,
		camoGhost,
		paranormalSound,
		spiritBox,
		ghostHunt,
		bansheeWail,
		teddyBear,
		spiritBoxBreath,
		motionSensor,
		shadowGhost,
		ghostGroan,
		ghostLaugh,
		ghostTalk,
		ghostWhisper,
		obakeFingerprint,
		burningChapelCrucifix,
		obakeShapeshift
	};
}

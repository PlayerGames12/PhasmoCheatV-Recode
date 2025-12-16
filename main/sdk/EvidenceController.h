#pragma once
#include "sdk.h"

namespace SDK
{
	struct EvidenceControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		ListEvidence* EvidenceList;
		void* roomsToSpawnDNAEvidenceInside;
		void* view;
		DNAEvidence* bone;
		Transform* GhostOrb;
		void* Field6;
		void* Field7;
		bool Field8;
		float Field9;
		void* Field10;
		float Field11;
		void* Field12;
	};

	struct EvidenceController
	{
		void* Clazz;
		void* Monitor;
		EvidenceControllerFields Fields;
	};

	DEC_MET(EvidenceController_Start, void(*)(EvidenceController* evidenceController, MethodInfo* methodInfo), "Assembly-CSharp", "", "EvidenceController", "Start", 0);
}

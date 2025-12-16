#pragma once
#include "sdk.h"

namespace SDK
{
	struct DNAEvidence;

	//DEC_MET(DNAEvidence_Start, void(*)(DNAEvidence* dnaEvidence, MethodInfo* methodInfo), "Assembly-CSharp", "", "DNAEvidence", "Start", 0); // Not need
	DEC_MET(DNAEvidence_GrabbedNetworked, void(*)(DNAEvidence* dnaEvidence, MethodInfo* methodInfo), "Assembly-CSharp", "", "DNAEvidence", "GrabbedNetworked", 0);
}
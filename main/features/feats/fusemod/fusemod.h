#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Map
{
	class FuseBoxModifier : public FeatureCore
	{
	public:
		FuseBoxModifier();
		~FuseBoxModifier() override = default;
		void OnActivate() override {};
		void OnDeactivate() override {};
		void OnRender() override {};
		void OnMenuRender() override;
		void FuseBoxModifierHandler();
	};
}
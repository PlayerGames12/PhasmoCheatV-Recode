#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class CrucifixModifier : public FeatureCore
	{
	public:
		CrucifixModifier();
		~CrucifixModifier() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;
		void CrucifixModifierHook(SDK::Crucifix* crucifix);
	};
}
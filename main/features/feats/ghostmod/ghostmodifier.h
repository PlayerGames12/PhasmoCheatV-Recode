#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Ghost
{
	class GhostModifier final : public FeatureCore
	{
	public:
		GhostModifier();
		~GhostModifier() override {}

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;
		void GhostModifierMain();
		void ChangeState(SDK::GhostState forcedState);
		void ForceAppear();
	};
}

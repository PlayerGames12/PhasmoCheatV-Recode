#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Players
{
	class CustomLookLimits final : public FeatureCore
	{
	public:
		CustomLookLimits();
		~CustomLookLimits() override = default;

		void OnActivate() override {}
		void OnDeactivate() override;
		void OnRender() override {}
		void OnMenuRender() override;

		void CustomLookLimitsMain(SDK::FirstPersonController* firstPersonController);
	};
}

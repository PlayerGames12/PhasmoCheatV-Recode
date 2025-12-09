#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Movement
{
	class CustomSpeed final : public FeatureCore
	{
	public:
		explicit CustomSpeed();
		~CustomSpeed() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

		void CustomSpeedMain(SDK::FirstPersonController* firstPersonController);
	};
}

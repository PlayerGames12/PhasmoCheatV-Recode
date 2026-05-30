#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class Spinbot final : public FeatureCore
	{
	public:
		explicit Spinbot();
		~Spinbot() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

		void SpinbotMain(SDK::FirstPersonController* firstPersonController);
	private:
		float m_spinAngle = 0.0f;
	};
}

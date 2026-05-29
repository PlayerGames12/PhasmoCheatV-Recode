#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class GhostSpin final : public FeatureCore
	{
	public:
		explicit GhostSpin();
		~GhostSpin() override = default;

		void OnActivate() override { m_basePosSet = false; }
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

		void GhostSpinMain(SDK::GhostAI* ghostAI);
	private:
		float m_spinAngle = 0.0f;
		SDK::Vector3 m_baseBodyPos = { 0, 0, 0 };
		float m_modelHeight = 0.0f;
		bool m_basePosSet = false;
	};
}

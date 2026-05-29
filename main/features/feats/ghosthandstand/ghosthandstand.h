#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class GhostHandstand final : public FeatureCore
	{
	public:
		explicit GhostHandstand();
		~GhostHandstand() override = default;

		void OnActivate() override { m_basePosSet = false; }
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

		void GhostHandstandMain(SDK::GhostAI* ghostAI);
	private:
		SDK::Vector3 m_baseBodyPos = { 0, 0, 0 };
		float m_modelHeight = 0.0f;
		bool m_basePosSet = false;
	};
}

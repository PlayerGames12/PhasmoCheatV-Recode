#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class GhostHandstand final : public FeatureCore
	{
	public:
		explicit GhostHandstand();
		~GhostHandstand() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

		void GhostHandstandMain(SDK::GhostAI* ghostAI);
	private:
		bool  m_applied = false;
		float m_offsetY = 0.0f;
	};
}

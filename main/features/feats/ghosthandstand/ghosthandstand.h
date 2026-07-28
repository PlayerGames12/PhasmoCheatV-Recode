#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class GhostHandstand final : public FeatureCore
	{
	public:
		explicit GhostHandstand();
		~GhostHandstand() override = default;

		void OnActivate() override { m_applied = false; }
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

		void GhostHandstandMain(SDK::GhostAI* ghostAI);
	private:
		bool  m_applied = false;
		float m_height = 1.8f;
		const SDK::Vector3 flippedScale = { 1.0f, -1.0f, 1.0f };
		const SDK::Vector3 normalScale = { 1.0f,  1.0f, 1.0f };
	};
}

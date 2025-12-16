#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
	class NotifyInfo final : public FeatureCore
	{
	public:
		NotifyInfo();
		~NotifyInfo() override = default;

		void OnActivate() override {};
		void OnDeactivate() override {};
		void OnRender() override {};
		void OnMenuRender() override;
		void RenderNotifyHunt(SDK::GhostAI* ghostAI, bool Hunting);
		void RenderNotifyBone();
	};
}

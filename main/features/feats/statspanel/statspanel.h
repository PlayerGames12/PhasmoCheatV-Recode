#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
	class StatsPanel final : public FeatureCore
	{
	public:
		StatsPanel();
		~StatsPanel() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override;
		void OnMenuRender() override;
		void StatsPanelCollectBone();
	private:
		bool collectBone = false;
	};
}

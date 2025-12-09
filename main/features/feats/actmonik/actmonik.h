#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
	class ActivityMonitor final : public FeatureCore
	{
	public:
		explicit ActivityMonitor();
		~ActivityMonitor() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override;
		void OnMenuRender() override;

	private:
		static constexpr ImGuiWindowFlags WINDOW_FLAGS =
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize;
	};
}

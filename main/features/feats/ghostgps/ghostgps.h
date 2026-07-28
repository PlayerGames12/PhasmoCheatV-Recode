#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
	class GhostGPS final : public FeatureCore
	{
	public:
		explicit GhostGPS();
		~GhostGPS() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override;
		void OnMenuRender() override;
	};
}
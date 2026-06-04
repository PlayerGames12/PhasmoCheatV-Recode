#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
	class StaminaPanel : public FeatureCore
	{
	public:
		StaminaPanel();
		~StaminaPanel() override = default;
		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override;
		void OnMenuRender() override;
	};
}
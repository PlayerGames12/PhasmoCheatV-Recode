#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class AutoGame : public FeatureCore
	{
	public:
		AutoGame();
		~AutoGame() override = default;
		void OnActivate() override {};
		void OnDeactivate() override {};
		void OnRender() override;
		void OnMenuRender() override;
		void AutoGameHandler();
	};
}
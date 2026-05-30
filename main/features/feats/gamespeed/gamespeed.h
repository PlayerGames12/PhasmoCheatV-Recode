#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class GameSpeed final : public FeatureCore
	{
	public:
		explicit GameSpeed();
		~GameSpeed() override = default;

		void OnActivate() override;
		void OnDeactivate() override;
		void OnRender() override {}
		void OnMenuRender() override;

		void GameSpeedMain();
	};
}

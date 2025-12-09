#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Movement
{
	class InfinityStamina final : public FeatureCore
	{
	public:
		InfinityStamina();
		~InfinityStamina() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

		void InfinityStaminaMain(SDK::PlayerStamina* playerStamina);
	};
}

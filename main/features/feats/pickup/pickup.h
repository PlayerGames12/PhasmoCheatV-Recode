#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Players
{
	class Pickup final : public FeatureCore
	{
	public:
		Pickup();
		~Pickup() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

		void PickupMain();
	};
}

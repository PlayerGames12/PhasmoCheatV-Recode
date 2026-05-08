#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class SpiritBoxAlwaysAnswer final : public FeatureCore
	{
	public:
		explicit SpiritBoxAlwaysAnswer();
		~SpiritBoxAlwaysAnswer() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {};
		void OnMenuRender() override;
	};
}
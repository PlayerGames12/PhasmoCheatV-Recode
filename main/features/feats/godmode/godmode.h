#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Players
{
	class GodMode final : public FeatureCore
	{
	public:
		GodMode();
		~GodMode() override = default;

		void OnActivate() override {};
		void OnDeactivate() override {};
		void OnRender() override {};
		void OnMenuRender() override;
	};
}
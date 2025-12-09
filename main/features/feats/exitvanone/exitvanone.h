#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class ExitVanOne final : public FeatureCore
	{
	public:
		ExitVanOne();
		~ExitVanOne() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

		bool ExitVanOneMain(SDK::ExitLevel* exitLevel, SDK::MethodInfo* methodInfo);
	};
}

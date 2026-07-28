#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
	class CrucifixESP : public FeatureCore
	{
	public:
		CrucifixESP();
		~CrucifixESP() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override;
		void OnMenuRender() override;

	private:
		std::vector<SDK::Crucifix*> getCruxifixs();
	};
}
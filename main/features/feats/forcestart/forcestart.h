#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class ForceStart final : public FeatureCore
	{
	public:
		ForceStart();
		~ForceStart() override = default;

		void OnActivate() override;
		void OnDeactivate() override;
		void OnRender() override {};
		void OnMenuRender() override;
		void ForceStartMain(SDK::ServerManager* serverManager);
	private:
		std::string SourceText = "";
	};
}

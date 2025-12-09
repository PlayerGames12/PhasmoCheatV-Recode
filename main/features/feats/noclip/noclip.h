#pragma once
#include "../Includes.h"
// Many thanks to Evelien for NoClip
namespace PhasmoCheatV::Features::Movement
{
	class NoClip final : public FeatureCore
	{
	public:
		explicit NoClip();
		~NoClip() override = default;

		void OnActivate() override {}
		void OnDeactivate() override;
		void OnRender() override {}
		void OnMenuRender() override;
		
		void NoClipMain(SDK::FirstPersonController* firstPersonController);
	};
}
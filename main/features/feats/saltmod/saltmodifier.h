#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Map
{
	class SaltModifier final : public FeatureCore
	{
	public:
		explicit SaltModifier();
		~SaltModifier() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;
		void SaltModifierMain();
		void SaltModifierMainNoUseGhost(SDK::SaltSpot* saltSpot, void* photon, SDK::MethodInfo* methodInfo);
	};
}
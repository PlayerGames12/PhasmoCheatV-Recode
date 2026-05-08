#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class ShopModifier final : public FeatureCore
	{
	public:
		explicit ShopModifier();
		~ShopModifier() override = default;

		void OnActivate() override;
		void OnDeactivate() override;
		void OnRender() override;
		void OnMenuRender() override;
		void ShopModifierMain();
	private:
		float lastUpdateTime = 0.0f;
		float lastTutorialLookupTime = 0.0f;
	};
}

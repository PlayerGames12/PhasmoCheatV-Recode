#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Players
{
	class SkipLayerAnim : public FeatureCore
	{
	public:
		SkipLayerAnim();
		~SkipLayerAnim() override = default;
		void OnActivate() override;
		void OnDeactivate() override;
		void OnRender() override {};
		void OnMenuRender() override;
		void SkipLayerAnimHandler();
	};
}
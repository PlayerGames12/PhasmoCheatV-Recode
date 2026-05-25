#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
	class AWEsp : public FeatureCore
	{
	public:
		AWEsp();
		~AWEsp() override = default;
		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override;
		void OnMenuRender() override;
	};
}
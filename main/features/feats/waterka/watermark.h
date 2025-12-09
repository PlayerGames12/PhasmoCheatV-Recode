#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
	class Watermark final : public FeatureCore
	{
	public:
		Watermark();
		~Watermark() override = default;

		void OnActivate() override {};
		void OnDeactivate() override {};
		void OnRender() override;
		void OnMenuRender() override;

	private:
		std::string CachedText;
	};
}
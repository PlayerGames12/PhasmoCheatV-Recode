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
		static constexpr std::string_view PING_PREFIX = " | Ping: ";
		static constexpr std::string_view SANITY_PREFIX = " | Avg. sanity: ";
	};
}
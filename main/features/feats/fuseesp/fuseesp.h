#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
	class FuseBoxESP final : public FeatureCore
	{
	public:
		explicit FuseBoxESP();
		~FuseBoxESP() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override;
		void OnMenuRender() override;

	private:
		std::string TextBuffer;
		static constexpr size_t INITIAL_BUFFER_SIZE = 32;
	};
}
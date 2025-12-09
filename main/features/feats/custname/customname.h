#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Players
{
	class CustomName final : public FeatureCore
	{
	public:
		explicit CustomName();
		~CustomName() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;
	private:
		char Name_Buff[128];
	};
}

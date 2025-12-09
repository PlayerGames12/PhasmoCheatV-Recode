#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Map
{
	class GrabKeys final : public FeatureCore
	{
	public:
		explicit GrabKeys();
		~GrabKeys() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;
		void GrabKeysAll();
		void GrabKeysMain();
	};
}

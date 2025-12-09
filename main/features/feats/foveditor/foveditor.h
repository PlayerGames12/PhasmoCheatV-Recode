#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Players
{
	class FoVEditor final : public FeatureCore
	{
	public:
		FoVEditor();
		~FoVEditor() override = default;

		void OnActivate() override {};
		void OnDeactivate() override {};
		void OnRender() override {};
		void OnMenuRender() override;
		void FoVEditorMain();
	};
}
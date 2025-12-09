#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Ghost
{
	class GhostInteractor final : public FeatureCore
	{
	public:
		GhostInteractor();
		~GhostInteractor() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;
		void GhostInteractorMain();

	private:
		bool TriggerLight = false;
		bool TriggerTwin = false;
		bool TriggerAbility = false;
		bool TriggerProp = false;
		bool TriggerGeneric = false;
		bool TriggerStandard = false;
		bool TriggerDoor = false;
	};
}

#pragma once // idea by ENZIO (phasmo cheat)
#include "../Includes.h"

namespace PhasmoCheatV::Features::Map
{
	class SoundBoard : public FeatureCore
	{
	public:
		SoundBoard();
		~SoundBoard() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;
	private:
		SDK::Door* getNearestDoor();
		void pLockSound();
		void pHuntingCloseDoorSound();
		void pSlamNoiseSound();
		void pRattlingNoiseSound();
		void pStopTruckSound();
		void pStartTruckSound();
	};
}
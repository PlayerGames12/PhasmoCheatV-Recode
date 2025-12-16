#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Movement
{
	class Teleport final : public FeatureCore
	{
	public:
		explicit Teleport();
		~Teleport() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

	private:
		enum class Target : int32_t
		{
			Ghost,
			Player
		};

		mutable bool HasSavedPoint = false;
		mutable SDK::Vector3 SavedPoint{};

		void SaveCurrentPosition();
		void TeleportToSavedPoint();
		void TeleportToCoordinates(float x, float y, float z);
		void TeleportItems();
		void TeleportBone();
		void TeleportToTruck();
		void TeleportToGhost();

		void ActivateAllWinterBoxes();
		void TeleportWinterBoxes();
		void UseAllWinterBoxes();
	};
}

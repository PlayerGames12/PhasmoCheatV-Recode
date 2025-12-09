#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class RewardModifier final : public FeatureCore
	{
	public:
		explicit RewardModifier();
		~RewardModifier() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

		int32_t RewardModifierMainBonus(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo);
		bool RewardModifierMainPrefGame(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo);
		int32_t RewardModifierMainMediaBonus(SDK::MediaValues* mediaValues, SDK::EvidenceQualityType qualityType, SDK::TierList mediaTier, SDK::MethodInfo* methodInfo);
		void RewardModifierObjectives(SDK::ObjectiveManager* objectiveManager);
	};
}
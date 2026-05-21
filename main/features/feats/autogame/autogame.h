#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class AutoGame : public FeatureCore
	{
	public:
		AutoGame();
		~AutoGame() override = default;
		void OnActivate() override {};
		void OnDeactivate() override;
		void OnRender() override;
		void OnMenuRender() override;
		void AutoGameHandler();
	private:
		static constexpr const char* mapItems[] = {
			"Random",
			"Tanglewood Drive",
			"Edgefield Road",
			"Ridgeview Court",
			"Nell's Diner",
			"Grafton Farmhouse",
			"Willow Street",
			"Point Hope",
			"Brownstone High School",
			"Bleasdale Farmhouse",
			"Sunny Meadows",
			"Sunny Meadows Restricted",
			"Prison",
			"Maple Lodge Campsite",
			"Camp Woodwind"
		};

		static constexpr int32_t mapIds[] = {
			-1, 4, 6, 7, 42, 10, 12, 15, 8, 9, 5, 5, 11, 13, 14
		};

		enum class AutoGamePhase
		{
			Idle,
			FindLobby,
			Voting,
			WaitingForVote,
			StartingGame,
			WaitingForPlayers,
			WaitingDelayAfterPlayers,
			CompletingObjectives,
			Exiting,
			SkipAndNext,
			Done
		};

		AutoGamePhase phase = AutoGamePhase::Idle;
		bool skipDone = false;
		bool nextDone = false;
		bool stopFlag = false;
		bool stopRequested = false;
		bool stopping = false;
		bool started = false;
		SDK::GameObject* cachedPostGame = nullptr;
		int32_t votedId = -1;
		int mapId = 0;
		std::chrono::steady_clock::time_point nextActionTime{};
		std::chrono::steady_clock::time_point waitStart{};
		int autoGameDelayMs = 0;
		const char* AutoGamePhaseToString(AutoGamePhase phase);
		int rewardedTotal = 0;
	};
}

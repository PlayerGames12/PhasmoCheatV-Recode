#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Misc
{
	class AntiKick final : public FeatureCore
	{
	public:
		AntiKick();
		~AntiKick() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

		void AntiKickMain(SDK::ServerManager* serverManager, bool isBanned, void* photonMessageInfo, SDK::MethodInfo* methodInfo);
	};
}

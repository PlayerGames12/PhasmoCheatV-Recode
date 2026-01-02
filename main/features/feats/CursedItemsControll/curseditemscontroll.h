#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Cursed
{
	class CursedItemsControll final : public FeatureCore
	{
	public:
		explicit CursedItemsControll();
		~CursedItemsControll() override = default;

		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override {}
		void OnMenuRender() override;

		void TarotCardApplySettings(SDK::TarotCardType& type);
		void TarotCardInfCards(SDK::TarotCards* tarotCards, SDK::MethodInfo* methodInfo);
	};
}

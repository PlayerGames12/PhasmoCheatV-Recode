#pragma once
#include "../includes.h"

namespace PhasmoCheatV
{
	class Menu
	{
	public:
		static void Initialize();
		static void NewYear();
		static void Render();
		static void Toggle();

		static inline bool Open = false;
		static inline bool Initialized = false;
		static inline int currentTab = 0;

	private:
		static SDK::CursorLockMode previousCursorLockMode;
	};

	inline Menu menu;
}
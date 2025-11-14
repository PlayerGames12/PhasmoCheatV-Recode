#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <iostream>
#include <thread>
#include <stdexcept>
#include <filesystem>
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <functional>
#include <Psapi.h>
#include <array>

#include "Globals.h"
#include "InGame.h"
#include "main/logging/logger.h"
#include "main/utils/utils.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "main/menu/renderer.h"

#include "main/sdk/sdk.h"
#include "detours/include/detours.h"
#include "main/hooks/Hooks.h"
#include "main/hooks/hooking.h"
#include "main/menu/menu.h"
#include "main/features/settings.h"
#include "main/features/feature.h"
#include "nlohmann/json.hpp"
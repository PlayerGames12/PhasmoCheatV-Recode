#pragma once
#include "../Includes.h"

#pragma comment(lib, "d3d11.lib")

namespace PhasmoCheatV
{
	using Id3DPresent = HRESULT(__stdcall*)(IDXGISwapChain* this_, UINT sync_, UINT flags_);

	class Renderer
	{
		const D3D_DRIVER_TYPE KDriverType[4] = {
			D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE, D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP
		};

	public:
		explicit Renderer();
		~Renderer();
		bool GetSwapChain(IDXGISwapChain** swapChain, ID3D11Device** device) const;
		Id3DPresent GetPresent() const;

		static inline IDXGISwapChain* Swapchain;
		static inline HWND Window;
		static inline ID3D11Device* Device;
		static inline ID3D11DeviceContext* Context;
		static inline ID3D11RenderTargetView* TargetView;
	};

	inline Renderer* renderer{};
}

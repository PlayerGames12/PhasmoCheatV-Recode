#include "renderer.h"

using namespace PhasmoCheatV;

Renderer::Renderer()
{
	renderer = this;
}

Renderer::~Renderer()
{
	renderer = nullptr;
}

bool Renderer::GetSwapChain(IDXGISwapChain** swapChain, ID3D11Device** device) const
{
	WNDCLASSEX wc{0};
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = TEXT("PhasmoCheatV");
	wc.hInstance = GetModuleHandle(nullptr);

	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	HWND hwnd = CreateWindowEx(
		0,
		wc.lpszClassName,
		TEXT(""),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		100,
		100,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr);

	if (!hwnd)
	{
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return false;
	}

	DXGI_SWAP_CHAIN_DESC description{};
	description.BufferCount = 1;
	description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	description.OutputWindow = hwnd;
	description.SampleDesc.Count = 1;
	description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	description.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	description.Windowed = TRUE;

	D3D_FEATURE_LEVEL level;
	bool success = false;

	for (const auto& driverType : KDriverType)
	{
		const HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, driverType, nullptr, 0, nullptr, 0,
		                                                 D3D11_SDK_VERSION, &description, swapChain, device, &level,
		                                                 nullptr);

		if (SUCCEEDED(hr))
		{
			success = true;
			break;
		}
	}

	DestroyWindow(hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);

	return success;
}

Id3DPresent Renderer::GetPresent() const
{
	IDXGISwapChain* swapChain;
	ID3D11Device* device;

	if (GetSwapChain(&swapChain, &device))
	{
		void** vmt = *reinterpret_cast<void***>(swapChain);

		if (swapChain)
		{
			swapChain->Release();
			swapChain = nullptr;
		}
		if (device)
		{
			device->Release();
			device = nullptr;
		}

		return static_cast<Id3DPresent>(vmt[8]);
	}

	return nullptr;
}

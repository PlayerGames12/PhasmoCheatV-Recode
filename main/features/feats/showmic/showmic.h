#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
	class ShowMicro : public FeatureCore
	{
	public:
		ShowMicro();
		~ShowMicro() override = default;
		void OnActivate() override {}
		void OnDeactivate() override {}
		void OnRender() override;
		void OnMenuRender() override;

	private:
		ID3D11ShaderResourceView* micOnSRV = nullptr;
		ID3D11ShaderResourceView* micOffSRV = nullptr;
		int micW = 0;
		int micH = 0;
		bool texturesLoaded = false;
		bool LoadFromMemory(unsigned char* data, size_t size, ID3D11ShaderResourceView** out_srv, int* w, int* h);
	};
}
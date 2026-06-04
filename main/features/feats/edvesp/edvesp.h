#pragma once
#include "../Includes.h"

namespace PhasmoCheatV::Features::Visuals
{
    class EvidenceESP final : public FeatureCore
    {
    public:
        explicit EvidenceESP();
        ~EvidenceESP() override = default;

        void OnActivate() override {}
        void OnDeactivate() override {}

        void OnRender() override;
        void OnMenuRender() override;

        void DrawIconText(const SDK::Vector3& screenPos,
            const std::string& icon,
            const std::string& text,
            ImColor color);
        void RenderEMF();
		void RenderEvidence();

        bool LoadFromMemory(unsigned char* data, size_t size, ID3D11ShaderResourceView** out_srv, int* w, int* h);
        void LoadTextures();
        void DrawTextureIcon(const SDK::Vector3& screenPos, ID3D11ShaderResourceView* tex, ImColor color);
        ID3D11ShaderResourceView* GetEvidenceTexture(SDK::EvidenceType type);
    };
}
#include "fontchanger.h"

using namespace PhasmoCheatV::Features::Visuals;
namespace fs = std::filesystem;

FontChanger::FontChanger() : FeatureCore(LANG("FontChanger_Header"), TYPE_VISUALS) 
{
    DECLARE_CONFIG(GetConfigManager(), "SelectedFont", std::string, "Arial");
}

void FontChanger::OnMenuRender()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));

    bool enabled = IsActive();
    if (ImGui::Checkbox(LANG("EnableFontChanger"), &enabled))
    {
        SET_CONFIG_VALUE(GetConfigManager(), "Enabled", bool, enabled);
        if (enabled) OnActivate();
        else OnDeactivate();
    }

    if (enabled)
    {
        std::string fontsPath = Utils::GetPhasmoCheatVDirectory() + "\\fonts";
        static std::vector<std::string> fontFiles;

        fontFiles.clear();
        for (auto& entry : fs::directory_iterator(fontsPath))
        {
            if (entry.is_regular_file())
            {
                auto ext = entry.path().extension().string();
                if (ext == ".ttf" || ext == ".otf")
                    fontFiles.push_back(entry.path().filename().string());
            }
        }

        std::string selectedFont = GET_CONFIG_VALUE(GetConfigManager(), "SelectedFont", std::string);

        if (ImGui::BeginCombo("##FontModifierCombo", selectedFont.c_str()))
        {
            for (auto& fontName : fontFiles)
            {
                bool isSelected = (selectedFont == fontName);
                if (ImGui::Selectable(fontName.c_str(), isSelected))
                {
                    selectedFont = fontName;
                    SET_CONFIG_VALUE(GetConfigManager(), "SelectedFont", std::string, selectedFont);
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }

    ImGui::PopStyleVar();
}

void FontChanger::FontChangerMain()
{
	if (!IsActive()) return;

    Il2CppClass* fontClass = il2cpp_get_class(
        "UnityEngine.TextRenderingModule",
        "UnityEngine",
        "Font"
    );

    if (!fontClass)
    {
        LOG_ERROR("Font class not found\n");
        return;
    }

    Il2CppObject* fontObj = il2cpp_object_new_from_class(fontClass);

    if (!fontObj)
    {
        LOG_ERROR("Failed to allocate Font\n");
        return;
    }

    std::string selectedFont = GET_CONFIG_VALUE(GetConfigManager(), "SelectedFont", std::string);
    std::string fullPath = Utils::GetPhasmoCheatVDirectory() + "\\fonts\\" + selectedFont;
    SDK::Font_ctor(reinterpret_cast<SDK::Font*>(fontObj), Utils::SysStrToUnityStr(fullPath), nullptr);
    SDK::TMP_FontAsset* tmpFont = SDK::CreateFontAsset(reinterpret_cast<SDK::Font*>(fontObj), nullptr);

    if (!tmpFont)
    {
        LOG_ERROR("Failed to create TMP_FontAsset\n");
        return;
    }

    auto* list = Utils::FindObjectsOfType("TMPro.TMP_Text, Unity.TextMeshPro");
    if (!list || list->MaxLength == 0)
    {
        LOG_ERROR("No TMP_Text components found");
        return;
    }

    uint32_t replaced = 0;
    for (uint32_t i = 0; i < list->MaxLength; i++)
    {
        SDK::Object* raw = list->Vector[i];
        if (!raw) continue;

        auto* tmpText = reinterpret_cast<SDK::TMP_Text*>(raw);

        SDK::TMP_Text_set_font(tmpText, tmpFont, nullptr);
        replaced++;
    }
}
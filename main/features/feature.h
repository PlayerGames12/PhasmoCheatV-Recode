#pragma once
#include "../Includes.h"

namespace PhasmoCheatV
{
    enum FeatureType : uint8_t
    {
        TYPE_NONE = 0,
        TYPE_VISUALS,
        TYPE_PLAYERS,
        TYPE_GHOST,
        TYPE_CURSED,
        TYPE_MISC,
        TYPE_MOVEMENT,
        TYPE_CONFIGS,
        TYPE_DIFFICULTY,
    };

    const char* GetFeatureTypeName(FeatureType type);

    class FeatureCore
    {
    public:
        explicit FeatureCore(const std::string_view name, const FeatureType type)
            : FeatureTitle(name), FeatureType(type), FeatureConfigs(std::make_unique<ConfigManager>())
        {
            DECLARE_CONFIG(FeatureConfigs.get(), "Enabled", bool, false);
        }

        FeatureCore(const FeatureCore&) = delete;
        FeatureCore& operator=(const FeatureCore&) = delete;
        FeatureCore(FeatureCore&&) noexcept = default;
        FeatureCore& operator=(FeatureCore&&) noexcept = default;
        virtual ~FeatureCore() = default;

        virtual void OnActivate() = 0;
        virtual void OnDeactivate() = 0;
        virtual void OnRender() = 0;
        virtual void OnMenuRender() = 0;

        [[nodiscard]] const std::string& GetFeatureTitle() const noexcept { return FeatureTitle; }
        [[nodiscard]] FeatureType GetFeatureType() const noexcept { return FeatureType; }
        [[nodiscard]] bool IsActive() const noexcept { return CONFIG_BOOL(FeatureConfigs.get(), "Enabled"); }
        [[nodiscard]] ConfigManager* GetConfigManager() noexcept { return FeatureConfigs.get(); }

        bool ShowInMenu = true;

    protected:
        std::string FeatureTitle;
        const FeatureType FeatureType;
        std::unique_ptr<ConfigManager> FeatureConfigs;
    };

    class FeatureHandler
    {
    public:
        FeatureHandler();
        ~FeatureHandler();

        FeatureType CurrentType = TYPE_NONE;

        void RegisterFeature(std::string_view name, std::unique_ptr<FeatureCore> feature);
        [[nodiscard]] const auto& GetFeatures() const noexcept { return FeatureRegistry; }
        [[nodiscard]] FeatureCore* FindFeature(std::string_view name) const;

        template <typename T>
        [[nodiscard]] T* GetFeature(std::string_view name) const
        {
            if (auto feature = FindFeature(name))
                return dynamic_cast<T*>(feature);
            return nullptr;
        }

        void RenderAll() const;
        void RenderMenu();

    private:
        std::unordered_map<std::string, std::unique_ptr<FeatureCore>> FeatureRegistry;
        void ShowTypeSelector();
        void ShowFeaturesByType();
    };

#define CREATE_FEATURE(ClassName, Category) \
    public: \
        ClassName() : FeatureCore(#ClassName, Category) {}

#define ADD_FEATURE(Handler, FeatureClass) \
        Handler->RegisterFeature(#FeatureClass, std::make_unique<FeatureClass>())

#define GET_FEATURE_HANDLER() (::PhasmoCheatV::MainFeatureHandler)

#define FEATURE_ENABLED(Feature) \
        (Feature->IsActive())

    inline FeatureHandler* MainFeatureHandler{};
}
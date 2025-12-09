#pragma once
#include "../Includes.h"
namespace PhasmoCheatV::Features::Map
{
    class MapModifier final : public FeatureCore
    {
    public:
        MapModifier();
        ~MapModifier() override = default;
        void OnActivate() override {}
        void OnDeactivate() override {}
        void OnRender() override {}
        void OnMenuRender() override;
        void MapModifierMain();
        void MapModifierMainAutoVote(SDK::LevelSelectionManager* levelSelectionManager);

    private:
        bool mapInitialize = false;

        enum MapNames : int32_t
        {
            TangleWoodDrive,
            EdgeFieldRoad,
            RidgeviewCourt,
            NellsDiner,
            GraftonFarmhouse,
            WillowStreet,
            PointHope,
            BrownstoneHighSchool,
            BleasdaleFarmhouse,
            SunnyMeadows,
            SunnyMeadowsRestricted,
            Prison,
            MapleLodgeCampsite,
            CampWoodwind
        };

        enum MapIdsAutoVote : int32_t
        {
            Map_Random = -1,
            Map_TangleWoodDrive = 4,
            Map_EdgeFieldRoad = 6,
            Map_RidgeviewCourt = 7,
            Map_NellsDiner,
            Map_GraftonFarmhouse = 10,
            Map_WillowStreet = 12,
            Map_PointHope = 15,
            Map_BrownstoneHighSchool = 8,
            Map_BleasdaleFarmhouse,
            Map_SunnyMeadows = 5,
            Map_SunnyMeadowsRestricted,
            Map_Prison = 11,
            Map_MapleLodgeCampsite = 13,
            Map_CampWoodwind = 14
        };

        MapNames currentMap = MapNames::TangleWoodDrive;
        MapIdsAutoVote selectedAutoVoteMap = MapIdsAutoVote::Map_Random;
        bool autoVoteInProgress = false;
        std::chrono::steady_clock::time_point autoVoteStartTime;

        MapNames GetMapEnumFromString(const std::string& name)
        {
            if (name.find("Tanglewood") != std::string::npos)
                return MapNames::TangleWoodDrive;
            if (name.find("Edgefield") != std::string::npos)
                return MapNames::EdgeFieldRoad;
            if (name.find("Ridgeview") != std::string::npos)
                return MapNames::RidgeviewCourt;
            if (name.find("Nell") != std::string::npos ||
                name.find("Diner") != std::string::npos)
                return MapNames::NellsDiner;
            if (name.find("Grafton") != std::string::npos)
                return MapNames::GraftonFarmhouse;
            if (name.find("Willow") != std::string::npos)
                return MapNames::WillowStreet;
            if (name.find("Point Hope") != std::string::npos ||
                name.find("PointHope") != std::string::npos)
                return MapNames::PointHope;
            if (name.find("Brownstone") != std::string::npos)
                return MapNames::BrownstoneHighSchool;
            if (name.find("Bleasdale") != std::string::npos)
                return MapNames::BleasdaleFarmhouse;
            if (name.find("Sunny Meadows Restricted") != std::string::npos)
                return MapNames::SunnyMeadowsRestricted;
            if (name.find("Sunny Meadows") != std::string::npos)
                return MapNames::SunnyMeadows;
            if (name.find("Prison") != std::string::npos)
                return MapNames::Prison;
            if (name.find("Maple Lodge") != std::string::npos)
                return MapNames::MapleLodgeCampsite;
            if (name.find("Camp Woodwind") != std::string::npos)
                return MapNames::CampWoodwind;
            return MapNames::TangleWoodDrive;
        }

        bool OnAllLights = false;
    };
}

#pragma once

#include "CppRestOpenAPIClient/model/ShipNavStatus.h"
#include "CppRestOpenAPIClient/model/WaypointTraitSymbol.h"
#include "CppRestOpenAPIClient/model/WaypointType.h"
#include "engine/scene/components.h"
#include "layer.h"
#include "sptr/data.h"
#include <sptr/sptr.h>

#include "sptr/events.h"
#include "util.h"
#include <engine/scene/entity.h>
#include <glm/glm.hpp>
#include <imgui.h>

inline const char* WAYPOINT_TRAITS = "UNCHARTED\0"
                                     "UNDER_CONSTRUCTION\0"
                                     "MARKETPLACE\0"
                                     "SHIPYARD\0"
                                     "OUTPOST\0"
                                     "SCATTERED_SETTLEMENTS\0"
                                     "SPRAWLING_CITIES\0"
                                     "MEGA_STRUCTURES\0"
                                     "PIRATE_BASE\0"
                                     "OVERCROWDED\0"
                                     "HIGH_TECH\0"
                                     "CORRUPT\0"
                                     "BUREAUCRATIC\0"
                                     "TRADING_HUB\0"
                                     "INDUSTRIAL\0"
                                     "BLACK_MARKET\0"
                                     "RESEARCH_FACILITY\0"
                                     "MILITARY_BASE\0"
                                     "SURVEILLANCE_OUTPOST\0"
                                     "EXPLORATION_OUTPOST\0"
                                     "MINERAL_DEPOSITS\0"
                                     "COMMON_METAL_DEPOSITS\0"
                                     "PRECIOUS_METAL_DEPOSITS\0"
                                     "RARE_METAL_DEPOSITS\0"
                                     "METHANE_POOLS\0"
                                     "ICE_CRYSTALS\0"
                                     "EXPLOSIVE_GASES\0"
                                     "STRONG_MAGNETOSPHERE\0"
                                     "VIBRANT_AURORAS\0"
                                     "SALT_FLATS\0"
                                     "CANYONS\0"
                                     "PERPETUAL_DAYLIGHT\0"
                                     "PERPETUAL_OVERCAST\0"
                                     "DRY_SEABEDS\0"
                                     "MAGMA_SEAS\0"
                                     "SUPERVOLCANOES\0"
                                     "ASH_CLOUDS\0"
                                     "VAST_RUINS\0"
                                     "MUTATED_FLORA\0"
                                     "TERRAFORMED\0"
                                     "EXTREME_TEMPERATURES\0"
                                     "EXTREME_PRESSURE\0"
                                     "DIVERSE_LIFE\0"
                                     "SCARCE_LIFE\0"
                                     "FOSSILS\0"
                                     "WEAK_GRAVITY\0"
                                     "STRONG_GRAVITY\0"
                                     "CRUSHING_GRAVITY\0"
                                     "TOXIC_ATMOSPHERE\0"
                                     "CORROSIVE_ATMOSPHERE\0"
                                     "BREATHABLE_ATMOSPHERE\0"
                                     "THIN_ATMOSPHERE\0"
                                     "JOVIAN\0"
                                     "ROCKY\0"
                                     "VOLCANIC\0"
                                     "FROZEN\0"
                                     "SWAMP\0"
                                     "BARREN\0"
                                     "TEMPERATE\0"
                                     "JUNGLE\0"
                                     "OCEAN\0"
                                     "RADIOACTIVE\0"
                                     "MICRO_GRAVITY_ANOMALIES\0"
                                     "DEBRIS_CLUSTER\0"
                                     "DEEP_CRATERS\0"
                                     "SHALLOW_CRATERS\0"
                                     "UNSTABLE_COMPOSITION\0"
                                     "HOLLOWED_INTERIOR\0"
                                     "STRIPPED\0\0";

template <typename Waypoint> void render_traits(const Waypoint& wp);
template <> inline void render_traits(const std::shared_ptr<models::ShipNavRouteWaypoint>& wp) {}

template <typename Waypoint> void render_waypoint(const Waypoint& wp, bool show_navigate_btn = true) {
    sptr::GameState& gs = sptr::GameState::instance();

    if (!gs.selected.ship) {
        return;
    }

    glm::vec2 here = gs.selected.ship.getComponent<TransformComponent>().getPosition();
    glm::vec2 there = glm::vec2(wp->getX(), wp->getY());
    int distance = glm::length(there - here);

    std::string header = fmt::format("{} ({}d)", wp->getSymbol(), distance);
    if (ImGui::CollapsingHeader(header.c_str())) {
        auto indent = sptr::ImIndent();

        ImGui::Text("Type: %s", wp->getType()->toJson().as_string().c_str());
        std::stringstream coords;
        coords << "(" << wp->getX() << "," << wp->getY() << ")";
        ImGui::LabelText("Coords", "%s", coords.str().c_str());

        sptr::Ship ship = gs.get_selected_ship();
        if (show_navigate_btn && ship &&
            ship->getNav()->getStatus()->getValue() !=
                models::ShipNavStatus::eShipNavStatus::ShipNavStatus_IN_TRANSIT) {

            ImGui::PushID(wp->getSymbol().c_str());
            if (ImGui::Button("Navigate")) {
                sptr::DataProvider::instance().request_ship_navigate_to_waypoint({ship}, wp);
            }
            ImGui::PopID();
            ImGui::SameLine();
        }
        ImGui::PushID((wp->getSymbol() + "ViewBtn").c_str());
        if (ImGui::Button("View")) {
            sptr::get_event_bus()->post(sptr::event::MapCenterOnWaypoint{wp->getSymbol()});
        }
        ImGui::PopID();

        render_traits(wp);
    }
}

template <typename Waypoint> void render_traits(const Waypoint& wp) {

#define DUMMY_BUTTON(traittype) ImGui::Button(#traittype);

    for (auto trait : wp->getTraits()) {

        switch (trait->getSymbol()->getValue()) {
            using wpt = models::WaypointTraitSymbol::eWaypointTraitSymbol;
            case wpt::WaypointTraitSymbol_SHIPYARD:
                ImGui::PushID((wp->getSymbol() + "shipyard").c_str());
                if (ImGui::Button("SHIPYARD")) {
                    sptr::DataProvider::instance().request_shipyard(wp);
                }
                ImGui::PopID();
                break;
            case wpt::WaypointTraitSymbol_MARKETPLACE:
                ImGui::PushID((wp->getSymbol() + "market").c_str());
                if (ImGui::Button("MARKETPLACE")) {
                    sptr::DataProvider::instance().request_marketplace(wp);
                }
                ImGui::PopID();
                break;
            case wpt::WaypointTraitSymbol_UNCHARTED:
                DUMMY_BUTTON(UNCHARTED);
                break;
            case wpt::WaypointTraitSymbol_UNDER_CONSTRUCTION:
                DUMMY_BUTTON(UNDER_CONSTRUCTION);
                break;
            case wpt::WaypointTraitSymbol_OUTPOST:
                DUMMY_BUTTON(OUTPOST);
                break;
            case wpt::WaypointTraitSymbol_SCATTERED_SETTLEMENTS:
                DUMMY_BUTTON(SCATTERED_SETTLEMENTS);
                break;
            case wpt::WaypointTraitSymbol_SPRAWLING_CITIES:
                DUMMY_BUTTON(SPRAWLING_CITIES);
                break;
            case wpt::WaypointTraitSymbol_MEGA_STRUCTURES:
                DUMMY_BUTTON(MEGA_STRUCTURES);
                break;
            case wpt::WaypointTraitSymbol_PIRATE_BASE:
                DUMMY_BUTTON(PIRATE_BASE);
                break;
            case wpt::WaypointTraitSymbol_OVERCROWDED:
                DUMMY_BUTTON(OVERCROWDED);
                break;
            case wpt::WaypointTraitSymbol_HIGH_TECH:
                DUMMY_BUTTON(HIGH_TECH);
                break;
            case wpt::WaypointTraitSymbol_CORRUPT:
                DUMMY_BUTTON(CORRUPT);
                break;
            case wpt::WaypointTraitSymbol_BUREAUCRATIC:
                DUMMY_BUTTON(BUREAUCRATIC);
                break;
            case wpt::WaypointTraitSymbol_TRADING_HUB:
                DUMMY_BUTTON(TRADING_HUB);
                break;
            case wpt::WaypointTraitSymbol_INDUSTRIAL:
                DUMMY_BUTTON(INDUSTRIAL);
                break;
            case wpt::WaypointTraitSymbol_BLACK_MARKET:
                DUMMY_BUTTON(BLACK_MARKET);
                break;
            case wpt::WaypointTraitSymbol_RESEARCH_FACILITY:
                DUMMY_BUTTON(RESEARCH_FACILITY);
                break;
            case wpt::WaypointTraitSymbol_MILITARY_BASE:
                DUMMY_BUTTON(MILITARY_BASE);
                break;
            case wpt::WaypointTraitSymbol_SURVEILLANCE_OUTPOST:
                DUMMY_BUTTON(SURVEILLANCE_OUTPOST);
                break;
            case wpt::WaypointTraitSymbol_EXPLORATION_OUTPOST:
                DUMMY_BUTTON(EXPLORATION_OUTPOST);
                break;
            case wpt::WaypointTraitSymbol_MINERAL_DEPOSITS:
                DUMMY_BUTTON(MINERAL_DEPOSITS);
                break;
            case wpt::WaypointTraitSymbol_COMMON_METAL_DEPOSITS:
                DUMMY_BUTTON(COMMON_METAL_DEPOSITS);
                break;
            case wpt::WaypointTraitSymbol_PRECIOUS_METAL_DEPOSITS:
                DUMMY_BUTTON(PRECIOUS_METAL_DEPOSITS);
                break;
            case wpt::WaypointTraitSymbol_RARE_METAL_DEPOSITS:
                DUMMY_BUTTON(RARE_METAL_DEPOSITS);
                break;
            case wpt::WaypointTraitSymbol_METHANE_POOLS:
                DUMMY_BUTTON(METHANE_POOLS);
                break;
            case wpt::WaypointTraitSymbol_ICE_CRYSTALS:
                DUMMY_BUTTON(ICE_CRYSTALS);
                break;
            case wpt::WaypointTraitSymbol_EXPLOSIVE_GASES:
                DUMMY_BUTTON(EXPLOSIVE_GASES);
                break;
            case wpt::WaypointTraitSymbol_STRONG_MAGNETOSPHERE:
                DUMMY_BUTTON(STRONG_MAGNETOSPHERE);
                break;
            case wpt::WaypointTraitSymbol_VIBRANT_AURORAS:
                DUMMY_BUTTON(VIBRANT_AURORAS);
                break;
            case wpt::WaypointTraitSymbol_SALT_FLATS:
                DUMMY_BUTTON(SALT_FLATS);
                break;
            case wpt::WaypointTraitSymbol_CANYONS:
                DUMMY_BUTTON(CANYONS);
                break;
            case wpt::WaypointTraitSymbol_PERPETUAL_DAYLIGHT:
                DUMMY_BUTTON(PERPETUAL_DAYLIGHT);
                break;
            case wpt::WaypointTraitSymbol_PERPETUAL_OVERCAST:
                DUMMY_BUTTON(PERPETUAL_OVERCAST);
                break;
            case wpt::WaypointTraitSymbol_DRY_SEABEDS:
                DUMMY_BUTTON(DRY_SEABEDS);
                break;
            case wpt::WaypointTraitSymbol_MAGMA_SEAS:
                DUMMY_BUTTON(MAGMA_SEAS);
                break;
            case wpt::WaypointTraitSymbol_SUPERVOLCANOES:
                DUMMY_BUTTON(SUPERVOLCANOES);
                break;
            case wpt::WaypointTraitSymbol_ASH_CLOUDS:
                DUMMY_BUTTON(ASH_CLOUDS);
                break;
            case wpt::WaypointTraitSymbol_VAST_RUINS:
                DUMMY_BUTTON(VAST_RUINS);
                break;
            case wpt::WaypointTraitSymbol_MUTATED_FLORA:
                DUMMY_BUTTON(MUTATED_FLORA);
                break;
            case wpt::WaypointTraitSymbol_TERRAFORMED:
                DUMMY_BUTTON(TERRAFORMED);
                break;
            case wpt::WaypointTraitSymbol_EXTREME_TEMPERATURES:
                DUMMY_BUTTON(EXTREME_TEMPERATURES);
                break;
            case wpt::WaypointTraitSymbol_EXTREME_PRESSURE:
                DUMMY_BUTTON(EXTREME_PRESSURE);
                break;
            case wpt::WaypointTraitSymbol_DIVERSE_LIFE:
                DUMMY_BUTTON(DIVERSE_LIFE);
                break;
            case wpt::WaypointTraitSymbol_SCARCE_LIFE:
                DUMMY_BUTTON(SCARCE_LIFE);
                break;
            case wpt::WaypointTraitSymbol_FOSSILS:
                DUMMY_BUTTON(FOSSILS);
                break;
            case wpt::WaypointTraitSymbol_WEAK_GRAVITY:
                DUMMY_BUTTON(WEAK_GRAVITY);
                break;
            case wpt::WaypointTraitSymbol_STRONG_GRAVITY:
                DUMMY_BUTTON(STRONG_GRAVITY);
                break;
            case wpt::WaypointTraitSymbol_CRUSHING_GRAVITY:
                DUMMY_BUTTON(CRUSHING_GRAVITY);
                break;
            case wpt::WaypointTraitSymbol_TOXIC_ATMOSPHERE:
                DUMMY_BUTTON(TOXIC_ATMOSPHERE);
                break;
            case wpt::WaypointTraitSymbol_CORROSIVE_ATMOSPHERE:
                DUMMY_BUTTON(CORROSIVE_ATMOSPHERE);
                break;
            case wpt::WaypointTraitSymbol_BREATHABLE_ATMOSPHERE:
                DUMMY_BUTTON(BREATHABLE_ATMOSPHERE);
                break;
            case wpt::WaypointTraitSymbol_THIN_ATMOSPHERE:
                DUMMY_BUTTON(THIN_ATMOSPHERE);
                break;
            case wpt::WaypointTraitSymbol_JOVIAN:
                DUMMY_BUTTON(JOVIAN);
                break;
            case wpt::WaypointTraitSymbol_ROCKY:
                DUMMY_BUTTON(ROCKY);
                break;
            case wpt::WaypointTraitSymbol_VOLCANIC:
                DUMMY_BUTTON(VOLCANIC);
                break;
            case wpt::WaypointTraitSymbol_FROZEN:
                DUMMY_BUTTON(FROZEN);
                break;
            case wpt::WaypointTraitSymbol_SWAMP:
                DUMMY_BUTTON(SWAMP);
                break;
            case wpt::WaypointTraitSymbol_BARREN:
                DUMMY_BUTTON(BARREN);
                break;
            case wpt::WaypointTraitSymbol_TEMPERATE:
                DUMMY_BUTTON(TEMPERATE);
                break;
            case wpt::WaypointTraitSymbol_JUNGLE:
                DUMMY_BUTTON(JUNGLE);
                break;
            case wpt::WaypointTraitSymbol_OCEAN:
                DUMMY_BUTTON(OCEAN);
                break;
            case wpt::WaypointTraitSymbol_RADIOACTIVE:
                DUMMY_BUTTON(RADIOACTIVE);
                break;
            case wpt::WaypointTraitSymbol_MICRO_GRAVITY_ANOMALIES:
                DUMMY_BUTTON(MICRO_GRAVITY_ANOMALIES);
                break;
            case wpt::WaypointTraitSymbol_DEBRIS_CLUSTER:
                DUMMY_BUTTON(DEBRIS_CLUSTER);
                break;
            case wpt::WaypointTraitSymbol_DEEP_CRATERS:
                DUMMY_BUTTON(DEEP_CRATERS);
                break;
            case wpt::WaypointTraitSymbol_SHALLOW_CRATERS:
                DUMMY_BUTTON(SHALLOW_CRATERS);
                break;
            case wpt::WaypointTraitSymbol_UNSTABLE_COMPOSITION:
                DUMMY_BUTTON(UNSTABLE_COMPOSITION);
                break;
            case wpt::WaypointTraitSymbol_HOLLOWED_INTERIOR:
                DUMMY_BUTTON(HOLLOWED_INTERIOR);
                break;
            case wpt::WaypointTraitSymbol_STRIPPED:
                DUMMY_BUTTON(STRIPPED);
                break;
        }
    }
}

inline const char* WAYPOINT_TYPES = "PLANET\0"
                                    "GAS_GIANT\0"
                                    "MOON\0"
                                    "ORBITAL_STATION\0"
                                    "JUMP_GATE\0"
                                    "ASTEROID_FIELD\0"
                                    "ASTEROID\0"
                                    "ENGINEERED_ASTEROID\0"
                                    "ASTEROID_BASE\0"
                                    "NEBULA\0"
                                    "DEBRIS_FIELD\0"
                                    "GRAVITY_WELL\0"
                                    "ARTIFICIAL_GRAVITY_WELL\0"
                                    "FUEL_STATION\0\0";

inline void render_shipyard(const sptr::Waypoint& wp) {}

struct WaypointsLayer : public Layer {
    void render() {
        const sptr::GameState& gs = sptr::GameState::instance();

        ImGui::Begin("Waypoints");

        ImGui::Combo("Type", &typeFilter, WAYPOINT_TYPES);
        ImGui::SameLine();
        ImGui::Combo("Traits", &traitFilter, WAYPOINT_TRAITS);

        auto view = gs.scene->view<sptr::WaypointComponent>();
        view.each([this](const auto& wpc) {
            sptr::Waypoint wp = wpc.waypoint;
            bool has_trait = false;

            for (auto& trait : wpc.waypoint->getTraits()) {
                if (trait->getSymbol()->getValue() ==
                    static_cast<models::WaypointTraitSymbol::eWaypointTraitSymbol>(traitFilter)) {
                    has_trait = true;
                    break;
                }
            }

            if (wp->getType()->getValue() == static_cast<models::WaypointType::eWaypointType>(typeFilter) &&
                has_trait) {

                render_waypoint(wpc.waypoint);
            }
        });

        ImGui::End();
    }
    int traitFilter = 0;
    int typeFilter = 0;
};

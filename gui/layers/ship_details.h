#pragma once

#include "CppRestOpenAPIClient/model/WaypointTraitSymbol.h"
#include "layer.h"

#include <sptr/sptr.h>

#include "ships.h"
#include "sptr/data.h"
#include "waypoints.h"

#include <imgui.h>

inline void render_route(sptr::ShipNavRoute route) {
    if (ImGui::CollapsingHeader("Route")) {
        auto indent = sptr::ImIndent();

        ImGui::Text("From");
        ImGui::SameLine();
        render_waypoint(route->getOrigin());

        ImGui::Text("To");
        ImGui::SameLine();
        render_waypoint(route->getDestination());

        ImGui::LabelText("Departure Time", "%s", route->getDepartureTime().to_string().c_str());
        ImGui::LabelText("Arrival", "%s", route->getArrival().to_string().c_str());
    }
}

struct ShipDetailsLayer : public Layer {
    void render() override {
        sptr::GameState& gs = sptr::GameState::instance();
        ship = gs.get_selected_ship();
        ImGui::Begin("Ship Details");

        if (ship) {
            ImGui::SeparatorText(ship->getSymbol().c_str());

            ImGuiTabBarFlags tab_bar_flags = (opt_fitting_flags) | (opt_reorderable ? ImGuiTabBarFlags_Reorderable : 0);
            if (ImGui::BeginTabBar("tabs", tab_bar_flags)) {
                if (ImGui::BeginTabItem("Status")) {

                    ImGui::Text("Location");
                    ImGui::SameLine();
                    auto wp = gs.get_waypoint(ship->getNav()->getWaypointSymbol());
                    if (wp) {
                        waypoint = wp;
                    }
                    if (waypoint) {
                        static const bool show_navigate_btn = false;
                        render_waypoint(waypoint, show_navigate_btn);
                    } else {
                        ImGui::Text("%s", ship->getNav()->getWaypointSymbol().c_str());
                    }

                    ImGui::Text("FlightMode");
                    ImGui::SameLine();
                    ImGui::Text("%s", ship->getNav()->getFlightMode()->toJson().as_string().c_str());

                    ImGui::Text("Nav Status");
                    ImGui::SameLine();
                    ImGui::Text("%s", ship->getNav()->getStatus()->toJson().as_string().c_str());

                    ::render(ship->getFuel());

                    switch (ship->getNav()->getStatus()->getValue()) {
                        case models::ShipNavStatus::eShipNavStatus::ShipNavStatus_IN_TRANSIT:
                            render_route(ship->getNav()->getRoute());
                            break;
                        case models::ShipNavStatus::eShipNavStatus::ShipNavStatus_IN_ORBIT:
                            if (ImGui::Button("Dock Ship")) {
                                sptr::DataProvider::instance().request_dock_ship({ship});
                            }
                            ImGui::SameLine();
                            if (ImGui::Button("Extract")) {
                                sptr::DataProvider::instance().request_ship_extract(ship);
                            }
                            break;
                        case models::ShipNavStatus::eShipNavStatus::ShipNavStatus_DOCKED:
                            if (ImGui::Button("Enter Orbit")) {
                                sptr::DataProvider::instance().request_orbit({ship});
                            }
                            ImGui::SameLine();
                            if (ImGui::Button("Refuel")) {
                                sptr::DataProvider::instance().request_ship_refuel(ship);
                            }
                            break;
                    }

                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Waypoints")) {
                    render_traits_combo();

                    gs.scene->view<sptr::WaypointComponent>().each([gs](const sptr::WaypointComponent& wpc) {
                        for (auto& trait : wpc.waypoint->getTraits()) {
                            if (trait->getSymbol()->getValue() ==
                                static_cast<models::WaypointTraitSymbol::eWaypointTraitSymbol>(gs.waypointsCombo)) {

                                render_waypoint(wpc.waypoint);
                            }
                        }
                    });

                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }
        }

        ImGui::End();
    }

    void render_traits_combo() {
        static const char* TRAITS = "UNCHARTED\0"
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

        sptr::GameState& gs = sptr::GameState::instance();
        ImGui::Combo("Traits", &gs.waypointsCombo, TRAITS);
    }

  private:
    sptr::Ship ship = nullptr;
    sptr::Waypoint waypoint = nullptr;
    bool opt_reorderable = true;
    ImGuiTabBarFlags opt_fitting_flags;
};

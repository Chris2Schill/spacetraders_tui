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

inline void render_traits_combo(int* selected) {
    ImGui::Combo("Traits", selected, WAYPOINT_TRAITS);
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

                sptr::GameState& gs = sptr::GameState::instance();
                if (ImGui::BeginTabItem("Waypoints")) {
                    render_traits_combo(&gs.waypointsCombo);

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

  private:
    sptr::Ship ship = nullptr;
    sptr::Waypoint waypoint = nullptr;
    bool opt_reorderable = true;
    ImGuiTabBarFlags opt_fitting_flags;
};

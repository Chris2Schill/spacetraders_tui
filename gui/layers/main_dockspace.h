#pragma once

#include "layer.h"
#include <engine/scene/components.h>

#include <imgui.h>
#include <sptr/sptr.h>

#include "main_menu.h"
#include <sptr/data.h>
#include "ui_game.h"
#include <entt/entt.hpp>

#include <app.h>
// struct GuiComponent {
//     std::vector<Ref<Layer>> layers;
// };
//
// struct MainDockspaceEntity {};

// inline void render_scene(Ref<Scene> scene) {
//     auto view = scene->view<GuiComponent>();
//
//     view.each([](const auto& gui) {
//         for (auto& layer : gui.layers) {
//             layer->render();
//         }
//     });
// }


struct MainDockspaceLayer : public Layer {
    MainDockspaceLayer() {
        sptr::get_event_bus()->subscribe<sptr::event::UserSelected>(this, &MainDockspaceLayer::on_user_selected);
    }

    void on_user_selected(const sptr::event::UserSelected& e) {
        sptr::GameState::instance().set_active_user(e.user);
        ui_game = std::make_shared<UIGame>();
        ui = ui_game;
    }

    void update() {
        update_ships();

        dp.update();
        ui->update();
    }

    void update_ships() {
        auto view = gs.scene->view<sptr::ShipComponent, TransformComponent>();
        // double dt = Application::get_instance()->get_timestep();
        double dt = 0.032; // TODO: FIX
        view.each([=](sptr::ShipComponent& shipc, TransformComponent& transform) {
            sptr::Ship ship = shipc.ship;

            switch (ship->getNav()->getStatus()->getValue()) {
                using sns = models::ShipNavStatus::eShipNavStatus;
                case sns::ShipNavStatus_IN_TRANSIT: {
                    const sptr::ShipNavRoute& route = ship->getNav()->getRoute();
                    glm::vec3 origin = glm::vec3(route->getOrigin()->getX(), route->getOrigin()->getY(), 0);
                    glm::vec3 dest = glm::vec3(route->getDestination()->getX(), route->getDestination()->getY(), 0);
                    std::cout << ship->getSymbol() << " IN TRANSIT: origin=" << route->getOrigin()->getSymbol()
                              << ", dest=" << route->getDestination()->getSymbol() << "\n";

                    const auto& start = route->getDepartureTime();
                    int trip_time_seconds = route->getArrival() - route->getDepartureTime();

                    shipc.flight_time += dt;
                    // double flight_time += dt;
                    // int flight_time = utility::datetime::utc_now() - start;

                    float pct = shipc.flight_time / static_cast<float>(trip_time_seconds);
                    pct = std::clamp(pct, 0.0f, 1.0f);
                    std::cout << "start=" << start.to_string() << ", trip_time=" << trip_time_seconds
                              << ", traveled_time= " << shipc.flight_time << ", pct=" << pct << "\n";

                    auto pos = glm::mix(origin, dest, pct);
                    transform.translation.x = pos.x;
                    transform.translation.y = pos.y;
                    transform.translation.z = pos.z;
                    transform.translation *= sptr::UNIVERSE_SCALE;

                    std::cout << ship->getSymbol() << " IN TRANSIT: origin=" << origin << ", dest=" << dest
                              << ", pct= " << pct << ", "
                              << "pos=" << transform.translation << "\n";

                    break;
                }
                case sns::ShipNavStatus_IN_ORBIT:
                case sns::ShipNavStatus_DOCKED: {
                    sptr::Waypoint wp = gs.get_waypoint(ship->getNav()->getWaypointSymbol());
                    if (wp) {
                        transform.translation.x = wp->getX();
                        transform.translation.y = wp->getY();
                        transform.translation.z = 0;
                        transform.translation *= sptr::UNIVERSE_SCALE;
                    }
                    break;
                }
            }
        });
    }

    void render() {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ui->render();
    }

    sptr::GameState gs;
    sptr::DataProvider dp = &gs;

    LayerPtr ui_mainmenu = std::make_shared<MainMenuLayer>();
    LayerPtr ui_game = nullptr;
    LayerPtr ui = ui_mainmenu;
};

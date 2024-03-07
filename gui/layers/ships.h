#pragma once

#include "layer.h"
#include "sptr/data.h"

#include <sptr/sptr.h>

#include "util.h"
#include <engine/core/timer.h>
#include <imgui.h>

template <typename T> void render_key_value(const char *key, const T &value) {
  std::string text = fmt::format("{}: {}", key, value);
  ImGui::Text("%s", text.c_str());
}

template <typename T> void render_description_of(const T &obj) {
  ImGui::TextWrapped("%s", obj->getDescription().c_str());
  ImGui::Spacing();
}

template <typename T> void render_requirements_for(const T &obj) {
  sptr::ShipRequirements ship_req = obj->getRequirements();
  if (ImGui::TreeNode("Requirements")) {
    if (int crew = ship_req->getCrew(); crew > 0) {
      ImGui::Text("Crew  - %d", crew);
    }

    if (int power = ship_req->getPower(); power > 0) {
      ImGui::Text("Power - %d", power);
    }

    if (int slots = ship_req->getSlots(); slots > 0) {
      ImGui::Text("Slots - %d", slots);
    }
    ImGui::TreePop();
  }
}

template <typename T> inline void render_condition_of(const T &obj) {
  // ImGui::Text("Condition       - %d", obj->getCondition());
  render_key_value("Condition", obj->getCondition());
}

template <typename T> inline void render_speed_of(const T &obj) {
  // ImGui::Text("Speed           - %d", obj->getSpeed());
  render_key_value("Speed", obj->getSpeed());
}

template <typename T> void render_power_output_of(const T &obj) {
  // ImGui::Text("Power Output    - %d", obj->getPowerOutput());
  render_key_value("Power Output", obj->getPowerOutput());
}

template <typename T> void render_fuel_capacity_of(const T &obj) {
  // ImGui::Text("Fuel Capacity   - %d", obj->getFuelCapacity());
  render_key_value("Fuel Capacity", obj->getFuelCapacity());
}

template <typename T> void render_module_slots_of(const T &obj) {
  // ImGui::Text("Module Slots    - %d", obj->getModuleSlots());
  render_key_value("Module slots", obj->getModuleSlots());
}

template <typename T> void render_mounting_points_of(const T &obj) {
  // ImGui::Text("Mounting Points - %d", obj->getMountingPoints());
  render_key_value("Mounting Points", obj->getMountingPoints());
}

inline void render(const sptr::ShipReactor &reactor) {
  if (ImGui::CollapsingHeader(fmt::format("Reactor - {} (po{})",
                                          reactor->getName(),
                                          reactor->getPowerOutput())
                                  .c_str())) {
    auto indent = sptr::ImIndent();
    render_description_of(reactor);
    render_power_output_of(reactor);
    render_requirements_for(reactor);
  }
}

inline void render(const sptr::ShipEngine &engine) {
  std::string header = fmt::format("Engine - {} (s{},c{})", engine->getName(),
                                   engine->getSpeed(), engine->getCondition());
  if (ImGui::CollapsingHeader(header.c_str())) {
    auto indent = sptr::ImIndent();
    render_description_of(engine);
    render_speed_of(engine);
    render_condition_of(engine);
    render_requirements_for(engine);
  }
}

inline void render(const sptr::ShipFrame &frame) {
  std::string header =
      fmt::format("Frame - {} (c{})", frame->getName(), frame->getCondition());

  if (ImGui::CollapsingHeader(header.c_str())) {
    auto indent = sptr::ImIndent();
    render_description_of(frame);
    render_condition_of(frame);
    render_fuel_capacity_of(frame);
    render_module_slots_of(frame);
    render_mounting_points_of(frame);
    render_requirements_for(frame);
  }
}

inline void render(const sptr::ShipRegistration &reg) {
  ImGui::LabelText(reg->getRole()->toJson().as_string().c_str(), "%s",
                   reg->getFactionSymbol().c_str());
}

inline void render(const sptr::ShipFuel &fuel) {
  ImGui::Text("Fuel %d/%d", fuel->getCurrent(), fuel->getCapacity());

  std::string overlay = fmt::format("{}/{}", fuel->getCurrent(), fuel->getCapacity());
  float pct = static_cast<float>(fuel->getCurrent()) / fuel->getCapacity();
  ImGui::ProgressBar(pct, ImVec2(80,20));
}
inline void render(const sptr::ShipMounts &mounts) {
  if (ImGui::CollapsingHeader("Mounts")) {
    auto indent = sptr::ImIndent();
    for (const auto &mount : mounts) {
      if (ImGui::CollapsingHeader(mount->getName().c_str())) {
        auto indent = sptr::ImIndent();
        render_key_value("Strength", mount->getStrength());
        if (ImGui::CollapsingHeader("Deposits")) {
          auto indent = sptr::ImIndent();
          for (const auto &deposit : mount->getDeposits()) {
            ImGui::Text("%s", deposit.c_str());
          }
        }
        render_requirements_for(mount);
      }
    }
  }
}
inline void render(const sptr::ShipModules &modules) {
  if (ImGui::CollapsingHeader("Modules")) {
    auto indent = sptr::ImIndent();
    for (const auto &module : modules) {
      if (ImGui::CollapsingHeader(module->getName().c_str())) {
        auto indent = sptr::ImIndent();
        render_description_of(module);
        render_key_value("Range", module->getRange());
        render_key_value("Capacity", module->getCapacity());
        render_requirements_for(module);
      }
    }
  }
}
inline void render(const sptr::ShipCrew &crew) {
  std::string header =
      fmt::format("Crew ({}/{})", crew->getCurrent(), crew->getCapacity());
  if (ImGui::CollapsingHeader(header.c_str())) {
    auto indent = sptr::ImIndent();
    render_key_value("Wage $/h", crew->getWages());
    render_key_value("Required", crew->getRequired());
    render_key_value("Rotation", crew->getRotation());
    render_key_value("Morale", crew->getMorale());
  }
}

inline void render_cargo(const sptr::Ship &ship) {
  sptr::ShipCargo cargo = ship->getCargo();

  std::string header =
      fmt::format("Cargo ({}/{})", cargo->getUnits(), cargo->getCapacity());
  if (ImGui::CollapsingHeader(header.c_str())) {
    auto indent = sptr::ImIndent();
    for (const sptr::ShipCargoItem &item : cargo->getInventory()) {
      std::string name =
          fmt::format("{} ({})", item->getName(), item->getUnits());
      if (ImGui::CollapsingHeader(name.c_str())) {
        auto indent = sptr::ImIndent();
        render_description_of(item);
        ImGui::PushID(&item);
        if (ImGui::Button("Sell")) {
          sptr::DataProvider::instance().request_sell_cargo(
              ship, item, item->getUnits());
        }
        ImGui::PopID();
      }
    }
  }
}

static void render_ship(const sptr::Ship &ship) {
  if (ImGui::CollapsingHeader(ship->getSymbol().c_str())) {

    auto indent = sptr::ImIndent();
    render(ship->getRegistration());
    render(ship->getFuel());
    render(ship->getFrame());
    render(ship->getEngine());
    render(ship->getReactor());
    render(ship->getCrew());
    render(ship->getMounts());
    render(ship->getModules());
    render_cargo(ship);

    ImGui::PushID(ship->getSymbol().c_str());
    if (ImGui::Button("View")) {
      sptr::DataProvider::instance().request_waypoints(
          ship->getNav()->getSystemSymbol().c_str());
      sptr::GameState::instance().selected.ship = ship;
    }
    ImGui::PopID();
  }
}

static bool g_opt_reorderable = true;
static ImGuiTabBarFlags g_opt_fitting_flags;

inline void render_ships(const sptr::Ships &ships) {
  ImGui::Begin("Ships");

  ImGuiTabBarFlags tab_bar_flags =
      (g_opt_fitting_flags) |
      (g_opt_reorderable ? ImGuiTabBarFlags_Reorderable : 0);

  if (ImGui::BeginTabBar("tabs", tab_bar_flags)) {
    if (ImGui::BeginTabItem("All")) {
      for (sptr::Ship ship : ships) {
        render_ship(ship);
      }
      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Explorers")) {
      for (sptr::Ship ship : ships) {
        if (ship->getRegistration()->getRole()->getValue() ==
            models::ShipRole::eShipRole::ShipRole_EXPLORER) {
          render_ship(ship);
        }
      }
      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Command")) {
      for (sptr::Ship ship : ships) {
        if (ship->getRegistration()->getRole()->getValue() ==
            models::ShipRole::eShipRole::ShipRole_COMMAND) {
          render_ship(ship);
        }
      }
      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Satellites")) {
      for (sptr::Ship ship : ships) {
        if (ship->getRegistration()->getRole()->getValue() ==
            models::ShipRole::eShipRole::ShipRole_SATELLITE) {
          render_ship(ship);
        }
      }
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  ImGui::End();
}

struct ShipsLayer : public Layer {
  void update() {
    if (timer.Elapsed() > 15) {
      timer.Reset();

      sptr::DataProvider::instance().request_ships();
    }
  }
  void render() {
    const sptr::GameState &gs = sptr::GameState::instance();
    render_ships(gs.ships);
  }

  Timer timer;
};

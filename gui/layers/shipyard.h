#pragma once

#include "layer.h"

#include <sptr/sptr.h>

#include "ships.h"
#include <imgui.h>

#include "sptr/data.h"
#include "util.h"



inline void render_shipyard(const sptr::Shipyard &shipyard) {
  if (!shipyard) {
    return;
  }

  ImGui::SeparatorText(shipyard->getSymbol().c_str());
  if (ImGui::CollapsingHeader("Ships")) {
    auto indent = sptr::ImIndent();
    for (auto &ship : shipyard->getShips()) {
      if (ImGui::CollapsingHeader(ship->getName().c_str())) {
        auto indent = sptr::ImIndent();
        ship->getSupply();
        ship->getActivity();
        ship->getType();
        render(ship->getFrame());
        render(ship->getEngine());
        render(ship->getReactor());
        render(ship->getMounts());
        render(ship->getModules());

        std::string buy = fmt::format("Buy ${}", ship->getPurchasePrice());
        ImGui::PushID(buy.c_str());
        if (ImGui::Button(buy.c_str())) {
            sptr::DataProvider::instance().request_purchase_ship(
                    shipyard->getSymbol(),
                    ship);
        }
        ImGui::PopID();
      }
    }
  }
}

struct ShipyardLayer : public Layer {
  void render() {
    const sptr::GameState &gs = sptr::GameState::instance();

    ImGui::Begin("Shipyard");
    render_shipyard(gs.selected.shipyard);

    ImGui::End();
  }
};

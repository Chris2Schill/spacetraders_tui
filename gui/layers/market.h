#pragma once

#include "layer.h"

#include <sptr/sptr.h>

#include <imgui.h>

#include "layers/ships.h"
#include "sptr/data.h"
#include "util.h"

inline void render_market(const sptr::Market &market) {
  if (!market) {
    return;
  }

  std::string header = fmt::format("Market - {}", market->getSymbol());
  if (ImGui::CollapsingHeader("Market")) {
    auto indent = sptr::ImIndent();
    if (market->importsIsSet()) {
      if (ImGui::CollapsingHeader("Imports")) {
        auto indent = sptr::ImIndent();

        for (const sptr::TradeGood &good : market->getImports()) {
          if (ImGui::CollapsingHeader(good->getName().c_str())) {
            auto indent = sptr::ImIndent();
            render_description_of(good);
          }
        }
      }
    }
    if (market->exportsIsSet()) {
      if (ImGui::CollapsingHeader("Exports")) {
          auto indent = sptr::ImIndent();
        for (const sptr::TradeGood &good : market->getExports()) {
          if (ImGui::CollapsingHeader(good->getName().c_str())) {
            auto indent = sptr::ImIndent();
            render_description_of(good);
          }
        }
      }
    }
  }
}

struct MarketplaceLayer : public Layer {
  void render() {
    const sptr::GameState &gs = sptr::GameState::instance();

    ImGui::Begin("Market");
    render_market(gs.selected.market);
    ImGui::End();
  }
};

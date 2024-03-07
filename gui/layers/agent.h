#pragma once

#include "layer.h"

#include <sptr/sptr.h>

#include <imgui.h>
#include <engine/core/timer.h>

struct AgentLayer : public Layer {
  AgentLayer() {
      timer.Reset();
  }

  void update() {
      if (timer.Elapsed() > 30) {
        sptr::DataProvider::instance().request_agent();
        timer.Reset();
      }
  }

  void render() {
    const sptr::GameState &gs = sptr::GameState::instance();

    if (!gs.my_agent) {
        return;
    }
    ImGui::Begin(gs.my_agent->getSymbol().c_str());

    ImGui::Text("Credits");
    ImGui::SameLine();
    ImGui::Text("$%ld", gs.my_agent->getCredits());

    ImGui::End();
  }

  Timer timer;
};

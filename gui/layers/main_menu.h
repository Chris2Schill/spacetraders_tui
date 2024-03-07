#pragma once

#include "layer.h"
#include <sptr/sptr.h>

#include <imgui.h>

struct MainMenuLayer : public Layer {
  MainMenuLayer() {}
  void update() override {}
  void render() override {
    ImGui::Begin("Users");
    // ImGui::DockBuilderDockWindow("Users", ImGui::GetID(MAIN_DOCKSPACE));
    for (const auto &user : sptr::GameState::get_users()) {
      if (ImGui::Selectable(user.name.c_str())) {
        sptr::get_event_bus()->post(sptr::event::UserSelected(&user));
      }
    }

    ImGui::End();
  }
};

#pragma once

#include "layer.h"
#include "log_window.h"
#include <sptr/sptr.h>

#include <imgui.h>

struct EventLogLayer : public Layer {
  EventLogLayer() {
    sptr::get_event_bus()->subscribe<sptr::event::LogEvent>(
        this, [this](const sptr::event::LogEvent &e) {
            log.AddLog("%s\n", e.msg.c_str());
        });
  }
  void render() {
    const sptr::GameState &gs = sptr::GameState::instance();

    log.Draw("EventLog");
    // ImGui::Begin("EventLog");
    //
    // ImGui::End();
  }

  AppLog log;
};

#pragma once

#include "layer.h"

#include <imgui.h>
#include <sptr/sptr.h>

#include "main_menu.h"
#include "ui_game.h"
#include <entt/entt.hpp>

struct MainDockspaceLayer : public Layer {
    MainDockspaceLayer() {
        sptr::get_event_bus()->subscribe<sptr::event::UserSelected>(
            this, &MainDockspaceLayer::on_user_selected);
    }

    void on_user_selected(const sptr::event::UserSelected& e) {
        ui_game = std::make_shared<UIGame>();
        sptr::GameState::instance().set_active_user(e.user);
        ui = ui_game;
        dp.remote_data_load_init();
    }

    void update() {
        dp.update();
        ui->update();
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

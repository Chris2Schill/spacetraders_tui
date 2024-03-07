#pragma once


#include <boost/numeric/conversion/detail/bounds.hpp>
#include <notcute/main_window.hpp>
#include "main_menu.hpp"
#include "dashboard.hpp"
#include <sptr/api.h>



using ContentPane = notcute::FrameWidget;



class SpaceTradersTui : public notcute::MainWindow {
public:
    SpaceTradersTui() {
        set_name("SpaceTraders TUI");

        main_menu = new MainMenu(this);
        get_layout()->add_widget(main_menu);

        main_menu->user_selected.connect([this](auto user){ user_selected(user); });
    }

    void user_selected(const sptr::User& user) {
        get_layout()->take(main_menu);
        dashboard = new Dashboard(&user, this);
        dashboard->get_layout()->set_behave(LAY_FILL| LAY_CENTER);
        get_layout()->add_widget(dashboard);
    }
    
private:
    MainMenu* main_menu = nullptr;
    Dashboard* dashboard = nullptr;
};


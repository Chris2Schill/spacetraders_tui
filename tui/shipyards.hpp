#pragma once

#include <notcute/event_loop.hpp>
#include <notcute/frame_widget.hpp>
#include <notcute/list_widget.hpp>
#include <notcute/logger.hpp>
#include <notcute/focus_stack.hpp>
#include <notcute/widget.hpp>
#include <CppRestOpenAPIClient/ApiClient.h>
#include <sptr/api.h>
#include "waypoints.hpp"
#include "util.h"

using Shipyard = std::shared_ptr<api::Shipyard>;
using ShipyardShip = std::shared_ptr<api::ShipyardShip>;
using ShipyardShipListItem = notcute::ListItem_t<ShipyardShip>;

namespace notcute {
    template<>
    inline std::string to_string<ShipyardShip>(const ShipyardShip& s) {
        return s->getName() + " - " + s->getType()->toJson().as_string();
    }
}

class Tmp : public notcute::Widget {
public:
    Tmp(Widget* parent = nullptr) :Widget(parent) {
        set_layout(new notcute::VBoxLayout);
    }
    
    void draw(ncpp::Plane* p) {
        // p->set_scrolling(true);
        // p->putstr(text.c_str());
        std::string line;
        std::stringstream ss(text);
        int i = 0;
        while (std::getline(ss, line, '\n')) {
            p->putstr(i,0,line.c_str());
            i++;
        }
    }

    std::string text= "BOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOII";
};
using namespace notcute;

class ShipyardContent : public notcute::FrameWidget {
public:
    ShipyardContent(Widget* shipyard_list, notcute::Widget* parent = nullptr)
        :FrameWidget(parent),
         api(sptr::get_api_client()),
         shipyard_list(shipyard_list)
    {
        set_layout(new notcute::HBoxLayout);
        set_focus_policy(notcute::FocusPolicy::FOCUS);

        ui.available_ships_list = new notcute::ListWidget(this);
        ui.available_ships_list->set_name("available ships list");
        ui.available_ships_list->set_title("Available Ships");
        ui.ship_view = new Tmp(this);

        get_layout()->add_widget(ui.available_ships_list);
        get_layout()->add_widget(ui.ship_view);

        ui.available_ships_list->item_hovered.connect([this](notcute::ListItem* item){
                ShipyardShip ship = notcute::list_widget_item_t_get_item<ShipyardShip>(item);
                auto str = sptr::pretty_json(ship->toJson().serialize());
                ui.ship_view->text = str;
                redraw();
            });
    }

    void request_data() {
        auto x = api.getShipyard(system_symbol,waypoint_symbol)
           .then([this](auto task){
                   API_ERROR_GUARD_START
                   auto shipyard = task.get()->getData();
                   auto event = new PayloadEvent(this, sptr::PAYLOAD_EVENT, shipyard);
                   notcute::EventLoop::get_instance()->post(event);
                   API_ERROR_GUARD_END
               });
    }

    bool on_event(notcute::Event* e) override {
        switch(static_cast<sptr::EventType>(e->get_type())) {
            case sptr::PAYLOAD_EVENT: {
                auto payload_event = static_cast<PayloadEvent<Shipyard>*>(e);
                shipyard = payload_event->get_payload();
                ui.available_ships_list->clear();
                log_debug("SHIPYARD AVAILSHIPS CLEARED");
                notcute::log_debug("{}", sptr::pretty_json(shipyard->toJson().serialize()));
                for (ShipyardShip s : shipyard->getShips()) {
                    auto item = new ShipyardShipListItem(s);
                    ui.available_ships_list->add_item(item);
                    log_debug("SHIPYARD AVAILSHIPS ADDED");
                }
                redraw();
                return true;
            }
            default:
                break;
        }

        return Widget::on_event(e);
    }

    bool on_keyboard_event(notcute::KeyboardEvent* e) override{
        switch(e->get_key()) {
            case NCKEY_ESC:
                shipyard_list->set_focus();
                return true;
            default:
                break;
        }

        if (ui.available_ships_list->on_keyboard_event(e)) {
            return true;
        }

        return FrameWidget::on_keyboard_event(e);;
    }

    void set_symbols(const std::string& system, const std::string& waypoint) {
        system_symbol = system;
        waypoint_symbol = waypoint;
        notcute::log_debug("set_symbols {} {}", system, waypoint);
        set_title(waypoint_symbol);
        ui.available_ships_list->clear();
        request_data();
        redraw();
    }

private:
    struct ui{
        notcute::ListWidget* available_ships_list;
        Tmp*     ship_view;
   }ui;

    api::SystemsApi api;

    std::string waypoint_symbol;
    std::string system_symbol;
    
    Shipyard shipyard;

    Widget* shipyard_list;
};

class ShipyardsList : public WaypointsList {
public:
    ShipyardsList(notcute::Widget* parent = nullptr)
        :WaypointsList(parent)
    {
        set_title("Shipyards");
        set_name("Shipyards");
        set_focus_policy(notcute::FocusPolicy::FOCUS);

        sy_content = new ShipyardContent(this, this);
        content_pane = sy_content;

        item_hovered.disconnect_all_slots();
        item_hovered.connect([this](notcute::ListItem* item){
                Waypoint wp = notcute::list_widget_item_t_get_item<Waypoint>(item);
                sy_content->set_symbols(wp->getSystemSymbol(), wp->getSymbol());
            });
    }

    notcute::Widget*  get_content_pane() const override { return sy_content; }

    bool on_keyboard_event(notcute::KeyboardEvent* e) override {
        switch(e->get_key()) {
            case NCKEY_ENTER:
                sy_content->set_focus();
                break;
            default:
                break;
        }

        return WaypointsList::on_keyboard_event(e);
    }

    void request_data() override {
        auto traits = std::make_shared<models::WaypointTraitSymbol>();
        traits->setValue(models::WaypointTraitSymbol::eWaypointTraitSymbol::WaypointTraitSymbol_SHIPYARD);
        // boost::optional<std::shared_ptr<WaypointTrait>> traitsopt = {traits};
        std::string tst = api::ApiClient::parameterToString(traits);
        notcute::log_debug("TRAITS={}, {}", tst, "SHIPYARD");
        // auto x = api.getSystemWaypoints(system_symbol,{}, 20, {}, {std::string("SHIPYARD")})
        auto x = api.getSystemWaypoints(system_symbol,{}, 20, {}, {traits})
           .then([this](auto task){
                   API_ERROR_GUARD_START
                   auto waypoints = task.get()->getData();
                   auto event = new PayloadEvent(this, sptr::PAYLOAD_EVENT, waypoints);
                   notcute::EventLoop::get_instance()->post(event);
                   API_ERROR_GUARD_END
               });
    }

    SPTR_FOCUS_HANDLER_IMPL

private:
    ShipyardContent* sy_content;
    
};

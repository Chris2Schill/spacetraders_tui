#pragma once


#include <notcute/frame_widget.hpp>
#include <notcute/list_widget.hpp>
#include <notcute/text_widget.hpp>
#include <CppRestOpenAPIClient/api/SystemsApi.h>
#include "notcute/widget.hpp"
#include "sptr_api.h"
#include "events.h"
#include "util.h"

using Waypoint = std::shared_ptr<api::Waypoint>;
using Waypoints = std::vector<Waypoint>;
using Label = notcute::TextWidget;

namespace notcute {
    template<>
    inline std::string to_string<Waypoint>(const Waypoint& w) {
        return w->getSymbol() + " - " + w->getType()->toJson().as_string();
    }
}
class WaypointWidget : public notcute::FrameWidget {
public:
    WaypointWidget(notcute::Widget* parent = nullptr)
        : notcute::FrameWidget(parent) {
        set_layout(new notcute::VBoxLayout);
        set_title("Waypoint");
        //
        // const int NUM_HBOXS = 2;
        // for (int i = 0; i < NUM_HBOXS; ++i) {
        //     notcute::Widget* wrapper = new notcute::Widget(this);
        //     auto hbox = new notcute::HBoxLayout(wrapper);
        //     hbox->set_margins_ltrb(1,1,1,1);
        //     ui.hboxs.push_back(hbox);
        //     get_layout()->add_widget(wrapper);
        // }
        //
        // ui.ship_name = new Label(this);
        // ui.role = new Label(this);
        // ui.faction = new Label(this);
        //
        // ui.hboxs[0]->get_layout()->add_widget(ui.ship_name);
        // ui.hboxs[0]->get_layout()->add_widget(ui.faction);
        // ui.hboxs[0]->get_layout()->add_widget(ui.role);
    }

    void draw(ncpp::Plane* p) {
        if (waypoint) {
            p->set_scrolling(true);
            auto pretty_json = sptr::pretty_json(waypoint->toJson().serialize());
            p->putstr(pretty_json.c_str());
        }
        FrameWidget::draw(p);
    }

    void set_waypoint(Waypoint w)
    {
        waypoint = w;
        // auto pretty_json = sptr::pretty_json(waypoint->toJson().serialize());
        // notcute::log_debug(pretty_json);
    }

private:
    // struct ui
    // {
    //     std::vector<notcute::HBoxLayout*> hboxs;
    //     Label* ship_name;
    //     Label* faction;
    //     Label* role;
    // }ui;

    Waypoint waypoint = nullptr;
};

class WaypointsList : public notcute::ListWidget {
public:
    using WaypointListItem = notcute::ListItem_t<Waypoint>;

    WaypointsList(notcute::Widget* parent = nullptr)
        :notcute::ListWidget(parent)
        ,api(sptr::get_api_client())
    {
        content_pane = new WaypointWidget(this);

        get_layout()->set_size(6, 0);
        get_layout()->set_behave(LAY_HFILL);
        set_title("Waypoints");
        set_name("Waypoints");
        set_focus_policy(notcute::FocusPolicy::FOCUS);


        item_hovered.connect([this](notcute::ListItem* item){
                Waypoint wp = notcute::list_widget_item_t_get_item<Waypoint>(item);
                if (auto cp = dynamic_cast<WaypointWidget*>(content_pane); cp) {
                    cp->set_waypoint(wp);
                    redraw_all();
                }
            });
    }

    virtual void request_data() {
        auto x = api.getSystemWaypoints(system_symbol,{}, 20, {}, {})
           .then([this](auto task){
                   API_ERROR_GUARD_START
                   auto waypoints = task.get()->getData();
                   auto event = new PayloadEvent(this, sptr::PAYLOAD_EVENT, waypoints);
                   notcute::EventLoop::get_instance()->post(event);
                   API_ERROR_GUARD_END
               });
    }

    bool on_event(notcute::Event* e) override {
        switch(static_cast<sptr::EventType>(e->get_type())) {
            case sptr::PAYLOAD_EVENT: {
                auto payload_event = static_cast<PayloadEvent<Waypoints>*>(e);
                waypoints = payload_event->get_payload();
                clear();
                for (Waypoint c : waypoints) {
                    auto item = new WaypointListItem(c);
                    add_item(item);
                }
                return true;
            }
            default:
                break;
        }

        return Widget::on_event(e);
    }

    bool on_keyboard_event(notcute::KeyboardEvent* e) override {
        if (sptr::handle_leftright(this, e)) {
            return true;
        }
        return ListWidget::on_keyboard_event(e);
    }

    void set_system_symbol(const std::string& symbol) {
        system_symbol = symbol;
        request_data();
    }

    virtual Widget* get_content_pane() const { return content_pane; }

    notcute::signal<void(Waypoint)> waypoint_selected;

    SPTR_FOCUS_HANDLER_IMPL

protected:
    Widget*     content_pane;
    std::string system_symbol;
    api::SystemsApi api;
    Waypoints waypoints;
};



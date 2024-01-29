#pragma once

#include <notcute/widget.hpp>
#include <notcute/spacer.hpp>
#include <notcute/focus_stack.hpp>

#include "agent.hpp"
#include "contracts.hpp"
#include "notcute/event_loop.hpp"
#include "ships.hpp"
#include "waypoints.hpp"
#include "shipyards.hpp"
#include "eventlog.hpp"

class Dashboard : public notcute::Widget {
public:
    Dashboard(const sptr::User* user, Widget* parent = nullptr)
        : Widget(parent)
    {
        set_name("Dashboard");
        set_layout(new notcute::VBoxLayout);
        set_focus_policy(notcute::FocusPolicy::FOCUS);

        main_widget = new notcute::Widget(this);
        main_widget->set_layout(new notcute::HBoxLayout);

        // auto title_widget = new TitleWidget(this);
        // title_widget->get_layout()->set_behave(LAY_TOP | LAY_HCENTER);
        // get_layout()->add_widget(title_widget);

        container = new notcute::FrameWidget(main_widget);
        container->set_layout(new notcute::VBoxLayout(0, 40));
        container->get_layout()->set_behave(LAY_LEFT | LAY_VFILL);
        container->set_title("container");

        panels = {
            .my_agent = new MyAgentWidget(user, container),
            .contracts = new ContractsListWidget(container),
            .ships     = new MyShipsWidget(container),
            .waypoints = new WaypointsList(container),
            .shipyards = new ShipyardsList(container),
            .event_log = new EventLogWidget(container),
        };

        container->get_layout()->add_widget(panels.my_agent);
        container->get_layout()->add_widget(panels.contracts);
        container->get_layout()->add_widget(panels.ships);
        container->get_layout()->add_widget(panels.waypoints);
        container->get_layout()->add_widget(panels.shipyards);
        container->get_layout()->add_widget(panels.event_log);
        container->get_layout()->add_widget(new notcute::Spacer(container));
        main_widget->get_layout()->add_widget(container);

        panel_content_container = new notcute::Widget(main_widget);
        panel_content_container->set_layout(new notcute::VBoxLayout);
        main_widget->get_layout()->add_widget(panel_content_container);

        get_layout()->add_widget(main_widget);

        auto* controls_text = new notcute::TextWidget("<l/h>: Next/Prev Panel, <j/k>: Scroll", this);
        // TODO: Why doesn't this margin work???? Temporary workaround by putting a space in the text string
        controls_text->get_layout()->set_margins_ltrb(1,0,0,0);
        controls_text->get_layout()->set_behave(LAY_LEFT | LAY_BOTTOM);
        controls_text->set_fg(notcute::BLUE);
        get_layout()->add_widget(controls_text);

        panels.ships->item_hovered.connect([this](notcute::ListItem* item){
                Ship ship = notcute::list_widget_item_t_get_item<Ship>(item);
                panels.waypoints->set_system_symbol(ship->getNav()->getSystemSymbol());
            });

        panels.ships->item_hovered.connect([this](notcute::ListItem* item){
                Ship ship = notcute::list_widget_item_t_get_item<Ship>(item);
                panels.shipyards->set_system_symbol(ship->getNav()->getSystemSymbol());
            });

        set_tab_order(panels.my_agent, panels.contracts);
        set_tab_order(panels.contracts, panels.ships);
        set_tab_order(panels.ships, panels.waypoints);
        set_tab_order(panels.waypoints, panels.shipyards);
        set_tab_order(panels.shipyards, panels.event_log);

        panels.my_agent->focus_changed.connect([this](bool focused) { if (focused) set_content_pane(panels.my_agent); });
        panels.contracts->focus_changed.connect([this](bool focused){ if (focused) set_content_pane(panels.contracts); });
        panels.ships->focus_changed.connect([this](bool focused)    { if (focused) set_content_pane(panels.ships); });
        panels.waypoints->focus_changed.connect([this](bool focused){ if (focused) set_content_pane(panels.waypoints); });
        panels.shipyards->focus_changed.connect([this](bool focused){ if (focused) set_content_pane(panels.shipyards); });
        // panels.event_log->focus_changed.connect([this](bool focused){ if (focused) set_content_pane(panels.event_log); });

        panels.my_agent->set_focus();
        focus_stack_push(this);
    }

    bool on_focus_in_event(notcute::FocusEvent* e) override {
        focus_next_in_chain();
        Widget* focused = Widget::get_focused_widget();
        // focus_stack_push(focused);
        return true;
    }

    template<typename T>
    void set_content_pane(T* wid) {
        log_debug("SET CONTENT PANE");
        panel_content_container->get_layout()->take(active_content_pane);
        panel_content_container->get_layout()->add_widget(wid->get_content_pane());
        active_content_pane = wid->get_content_pane();
        // TODO shouldn't need to redraw
        redraw();
    }

private:
    notcute::Widget* panel_content_container = nullptr;
    notcute::Widget* active_content_pane = nullptr;

    notcute::Widget*          main_widget = nullptr;
    notcute::FrameWidget*     container = nullptr;
    struct {
        MyAgentWidget*        my_agent = nullptr;
        ContractsListWidget*  contracts = nullptr;
        MyShipsWidget*        ships = nullptr;
        WaypointsList*        waypoints = nullptr;
        ShipyardsList*        shipyards = nullptr;
        EventLogWidget*       event_log = nullptr;

    } panels;
};

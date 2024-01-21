#pragma once

#include <notcute/widget.hpp>
#include <notcute/spacer.hpp>

#include "focus_node.hpp"
#include "agent.hpp"
#include "contracts.hpp"
#include "ships.hpp"
#include "util.h"
#include "waypoints.hpp"
#include "shipyards.hpp"
#include "eventlog.hpp"
#include "util.h"
#include "main_menu.hpp"

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
        controls_text->get_plane()->set_fg_palindex(4);
        get_layout()->add_widget(controls_text);

        panels.ships->item_hovered.connect([this](notcute::ListItem* item){
                Ship ship = notcute::list_widget_item_t_get_item<Ship>(item);
                panels.waypoints->set_system_symbol(ship->getNav()->getSystemSymbol());
            });

        panels.ships->item_hovered.connect([this](notcute::ListItem* item){
                Ship ship = notcute::list_widget_item_t_get_item<Ship>(item);
                panels.shipyards->set_system_symbol(ship->getNav()->getSystemSymbol());
            });

        std::vector<FocusNode*> focus_nodes = setup_focus_graph({
            {panels.my_agent,  panels.my_agent->get_content_pane()},
            {panels.contracts, panels.contracts->get_content_pane()},
            {panels.ships,     panels.ships->get_content_pane()},
            {panels.waypoints, panels.waypoints->get_content_pane()},
            {panels.shipyards, panels.shipyards->get_content_pane()},
            {panels.event_log, nullptr},
        });
        focus_graph_node = focus_nodes.front();
        set_active_focus_node(focus_nodes.front());
        focus_stack_push({this, &focus_graph_node});
    }

    bool on_keyboard_event(notcute::KeyboardEvent* e) override {

        switch(e->get_key()) {
            case 'l':
            case NCKEY_RIGHT:
                set_active_focus_node(focus_graph_node->next);
                return true;
            case 'h':
            case NCKEY_LEFT:
                set_active_focus_node(focus_graph_node->prev);
                return true;
            default:
                break;
        }

        if (focus_graph_node->widget->on_keyboard_event(e)) {
            return true;
        }

        return Widget::on_keyboard_event(e);
    }

    void set_active_focus_node(FocusNode* node) {
        notcute::Widget* from_wid = static_cast<notcute::Widget*>(focus_graph_node->userptr);
        notcute::Widget* to_wid   = static_cast<notcute::Widget*>(node->userptr);

        focus_graph_node->off_focus_callback();

        // remove it
        panel_content_container->get_layout()->take(from_wid);

        // add in the new current nodes content
        if (to_wid) {
            panel_content_container->get_layout()->add_widget(to_wid);
        }

        focus_graph_node = node;
        focus_graph_node->on_focus_callback();
        notcute::log_debug("FOCUS ON " + focus_graph_node->widget->get_name());
        redraw();
    }

private:
    FocusNode* focus_graph_node;
    notcute::Widget* panel_content_container = nullptr;

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

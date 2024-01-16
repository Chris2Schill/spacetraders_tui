#pragma once


#include <boost/numeric/conversion/detail/bounds.hpp>
#include <notcute/main_window.hpp>
#include <notcute/frame_widget.hpp>
#include <notcute/text_widget.hpp>
#include <notcute/event_loop.hpp>
#include <notcute/widget.hpp>
#include <notcute/list_widget.hpp>
#include <notcute/renderer.hpp>
#include <CppRestOpenAPIClient/api/AgentsApi.h>
#include <CppRestOpenAPIClient/api/ContractsApi.h>
#include "main_menu.hpp"
#include "help_menu.hpp"
#include "notcute/include/notcute/scroll_area.hpp"
#include "sptr_api.h"


namespace sptr {
    enum EventType {
        PAYLOAD_EVENT = notcute::Event::USER_EVENT,
        EVENTLOG_EVENT,
    };
}


using ContractPtr = std::shared_ptr<api::Contract>;
using Contracts = std::vector<ContractPtr>;

class ContentPane : public notcute::FrameWidget {
public:
    using notcute::FrameWidget::FrameWidget;

    void draw(ncpp::Plane* p) override {
        FrameWidget::draw(p);
    }
};

class ContractWidget : public notcute::Widget {
public:
    ContractWidget(notcute::Widget* parent = nullptr)
        :notcute::Widget(parent)
    {
        set_layout(new notcute::VBoxLayout);
        get_layout()->set_margins_ltrb(1,1,1,1);
    }

    void set_contract(ContractPtr c) {
        contract = c;
        redraw();
    }

    void draw(ncpp::Plane* p) {
        // notcute::fill(p, "z");
        if (contract) {
            std::string accepted = contract->isAccepted() ? "ACCEPTED" : "PENDING";
            p->printf(0,0,  "ID: %s           %s", contract->getId().c_str(), accepted.c_str());
            p->printf(1,0,  "Faction: %s", contract->getFactionSymbol().c_str());
            p->printf(2,0,  "Type: %s", contract->getType().c_str());
            p->printf(3,0,  "Terms:");
            p->printf(4,0,  "    Deadline: %s", contract->getTerms()->getDeadline().to_string().c_str());
            p->printf(5,0,  "    Payment:");
            p->printf(6,0,  "        On Accepted:  $%d", contract->getTerms()->getPayment()->getOnAccepted());
            p->printf(7,0,  "        On Fulfilled: $%d", contract->getTerms()->getPayment()->getOnFulfilled());
            p->printf(9,0,  "    Deliver:");

            auto& goods = contract->getTerms()->getDeliver();
            // if (!destinationSelectable) {
            //     destinationSelectable = new Selectable(itemContents, 10, 22, goods[0]->getDestinationSymbol());
            // }
            p->printf(9,0, "        %ld Payloads: %s %d/%d", goods.size(), goods[0]->getTradeSymbol().c_str(), goods[0]->getUnitsFulfilled(), goods[0]->getUnitsRequired());

            // itemContents->printf(10,0, "        Destination: %s", goods[0]->getDestinationSymbol().c_str());
            p->printf(10,0, "        Destination: %s", goods[0]->getDestinationSymbol().c_str());
        }
    }

    ContractPtr contract = nullptr;

};

class ContractsContentPane : public ContentPane {
public:
    ContractsContentPane(notcute::Widget* parent = nullptr)
        :ContentPane(parent)
    {
        set_layout(new notcute::VBoxLayout);
        // get_layout()->add_widget(new notcute::TextWidget("CONTRACTS BABY", this));
        get_layout()->set_size(100,100);
        // get_layout()->set_margins_ltrb(1,1,1,1);
        // get_layout()->set_behave(LAY_FILL);
        cw = new ContractWidget(this);

        get_layout()->add_widget(cw);

        set_title("Contracts");
    }

    void set_contract(ContractPtr c) {
        cw->set_contract(c);
    }

    ContractWidget* cw = nullptr;
};

static const std::string test1  = "▀█▀ ██▀ ▀▄▀ ▀█▀   ██▀ █▀▄ █ ▀█▀ ▄▀▄ █▀▄";
 static const std::string test2 = " █  █▄▄ █ █  █    █▄▄ █▄▀ █  █  ▀▄▀ █▀▄";

class MyAgentContentPane : public ContentPane {
public:
    MyAgentContentPane(notcute::Widget* parent = nullptr)
        :ContentPane(parent)
    {
        set_layout(new notcute::VBoxLayout);
        get_layout()->set_size(100,100);
        set_title("MYAGENET");
    }

    void draw(ncpp::Plane* p) {

        p->perimeter_rounded(0,0,0);
        p->putstr(1,1,test1.c_str());
        p->putstr(2,1,test2.c_str());
    }

};

// Allows a content pane to be driven through the draw pipeline
// of the ContentPaneDrawer subclass without having the
// ContentPane be a direct child of the ContentPaneDrawer
class ContentPaneDrawer : public notcute::Widget{
public:
    ContentPaneDrawer(notcute::Widget* parent = nullptr) : notcute::Widget(parent) {
        set_focus_policy(notcute::FocusPolicy::FOCUS);
    }

    virtual ContentPane* get_content_pane() = 0;

    virtual void pre_draw(ncpp::Plane* p) override {
        Widget::pre_draw(p);
        if (ContentPane* cp = get_content_pane(); cp) {
            cp->pre_draw(cp->get_plane());
        }
    }

    void draw(ncpp::Plane* p) override {
        notcute::Widget::draw(p);
        if (ContentPane* cp = get_content_pane(); cp) {
            cp->pre_draw(cp->get_plane());
        }
    }

    bool on_keyboard_event(notcute::KeyboardEvent* e) override {
        switch(e->get_key()) {
            case 'l':
            case NCKEY_DOWN:
                on_next_pane();
                return true;
            case 'h':
            case NCKEY_UP:
                on_prev_pane();
                return true;
            default:
                return false;
        }
        return Widget::on_event(e);
    }

    notcute::signal<void()> on_next_pane;
    notcute::signal<void()> on_prev_pane;
};

// class FocusListWidgetItem {
//     FocusListWidgetItem(notcute::Widget*)
//
// };
//
// class FocusListWidget : public notcute::Widget {
// public:
//     using notcute::Widget::Widget;
//
//     void add_widget(notcute::Widget* w) {
//     }
// private:
//
//     std::vector<FocusListWidgetItem*> items;
// };
//


template<typename T>
class PayloadEvent : public notcute::Event {
public:
    PayloadEvent(notcute::Widget* sender,
                 int type,
                 const T& p)
        : notcute::Event(sender, static_cast<notcute::Event::EventType>(type))
        , payload(p)
    {}

    const T& get_payload() const { return payload; }


private:
    notcute::Event::EventType type;
    T payload;
};


namespace notcute {
    template<>
    std::string to_string<ContractPtr>(const ContractPtr& c) {
        return c->getId();
    }
}

class ContractsListWidget : public ContentPaneDrawer {
public:

    using ContractListItem = notcute::ListItem_t<ContractPtr>;

    ContractsListWidget(const sptr::User* user, Widget* parent = nullptr)
        : ContentPaneDrawer(parent)
        , api(sptr::get_api_client())
    {
        new notcute::VBoxLayout(this);
        request_data();
        get_layout()->set_size(6, 0);
        get_layout()->set_behave(LAY_HFILL);

        contracts_list = new notcute::ListWidget(this);

        Widget::focus_state_changed.connect([this](bool focus){ focus_state_changed(focus); });

        content_pane = new ContractsContentPane;

        contracts_list->item_hovered.connect([this](notcute::ListItem* item){
                ContractPtr contract = notcute::list_widget_item_t_get_item<ContractPtr>(item);
                notcute::log_debug("selected contract! " + contract->getId());
                content_pane->set_contract(contract);
                
            });

        get_layout()->add_widget(contracts_list);
    }


    bool on_event(notcute::Event* e) override {
        switch(static_cast<sptr::EventType>(e->get_type())) {
            case sptr::PAYLOAD_EVENT: {
                auto payload_event = static_cast<PayloadEvent<Contracts>*>(e);
                contracts = payload_event->get_payload();
                contracts_list->clear();
                for (ContractPtr c : contracts) {
                    notcute::log_debug(c->toJson().serialize());
                    auto item = new ContractListItem(c);
                    contracts_list->add_item(item);
                }
                return true;
            }
            default:
                break;
        }

        return Widget::on_event(e);
    }

    ContentPane* get_content_pane() override { return content_pane; }

    bool on_keyboard_event(notcute::KeyboardEvent* e) override {
        if (contracts_list->on_keyboard_event(e)) {
            return true;
        }

        switch(e->get_key()) {
            case '?':
                show_help_menu();
                return true;
            default:
                return ContentPaneDrawer::on_keyboard_event(e);
        }
    }

    void request_data() {
        api.getContracts({},{})
           .then([this](auto task){
                   auto new_contracts = task.get()->getData();
                   auto event = new PayloadEvent(this, sptr::PAYLOAD_EVENT, new_contracts);
                   notcute::EventLoop::get_instance()->post(event);
               });
    }

    // void draw(ncpp::Plane* p) override {
    //     notcute::ListWidget::draw(p);
    // }

    void focus_state_changed(bool focus) {
        int pal_index = focus ? 200 : 1;
        if (auto* frame = dynamic_cast<notcute::FrameWidget*>(get_parent()); frame) {
            frame->get_plane()->set_fg_palindex(pal_index);
            frame->redraw();
        }
    }

    ContractPtr get_selected_contract() {
        return contracts[contracts_list->get_selected_idx()];
    }

    void show_help_menu() {
        auto fw = new HelpMenu({ {"c", "do some cool shizzz"},
                                 {"<pageup>", "somemore coool shizzzz"}}, get_top_level_widget());
        // fw->move_to_term_center();
        // fw->redraw();
        fw->show();
        delete fw;
        redraw();
    }


    // void draw_content_pane() override {
    //     if (contracts.empty()) { return; }
    //
    //
    //     ncpp::Plane* p = get_content_pane()->get_plane();
    //     p->putstr(1,1,"BOIIIII");
    //     
    //     ContractPtr contract = get_selected_contract();
    //     if (contract) {
    //         std::string accepted = contract->isAccepted() ? "ACCEPTED" : "PENDING";
    //         p->printf(0,0,  "ID: %s           %s", contract->getId().c_str(), accepted.c_str());
    //         p->printf(1,0,  "Faction: %s", contract->getFactionSymbol().c_str());
    //         p->printf(2,0,  "Type: %s", contract->getType().c_str());
    //         p->printf(3,0,  "Terms:");
    //         p->printf(4,0,  "    Deadline: %s", contract->getTerms()->getDeadline().to_string().c_str());
    //         p->printf(5,0,  "    Payment:");
    //         p->printf(6,0,  "        On Accepted:  $%d", contract->getTerms()->getPayment()->getOnAccepted());
    //         p->printf(7,0,  "        On Fulfilled: $%d", contract->getTerms()->getPayment()->getOnFulfilled());
    //         p->printf(9,0,  "    Deliver:");
    //
    //         auto& goods = contract->getTerms()->getDeliver();
    //         // if (!destinationSelectable) {
    //         //     destinationSelectable = new Selectable(itemContents, 10, 22, goods[0]->getDestinationSymbol());
    //         // }
    //         p->printf(9,0, "        %ld Payloads: %s %d/%d", goods.size(), goods[0]->getTradeSymbol().c_str(), goods[0]->getUnitsFulfilled(), goods[0]->getUnitsRequired());
    //
    //         // itemContents->printf(10,0, "        Destination: %s", goods[0]->getDestinationSymbol().c_str());
    //         p->printf(10,0, "        Destination: %s", goods[0]->getDestinationSymbol().c_str());
    //     }
    //
    //     cp->redraw();
    // };

private:
    notcute::ListWidget* contracts_list;

    api::ContractsApi api;
    Contracts contracts;

    ContractsContentPane* content_pane;
};

class MyAgentWidget : public ContentPaneDrawer {
public:
    using Agent = std::shared_ptr<api::Agent>;

    MyAgentWidget(const sptr::User* user, Widget* parent = nullptr)
        : ContentPaneDrawer(parent)
        , api(sptr::get_api_client())
    {
        new notcute::VBoxLayout(this);
        request_data();
        get_layout()->set_size(6, 0);
        get_layout()->set_behave(LAY_HFILL);
        content_pane = new MyAgentContentPane(this);
    }

    void request_data() {
        api.getMyAgent()
           .then([this](auto x){
                   auto agent = x.get()->getData();
                   auto event = new PayloadEvent(this, sptr::PAYLOAD_EVENT, agent);
                   notcute::EventLoop::get_instance()->post(event);
               });
    }

    bool on_event(notcute::Event* e) {
        switch(static_cast<sptr::EventType>(e->get_type())) {
            case sptr::PAYLOAD_EVENT: {
                auto payload_event = static_cast<PayloadEvent<Agent>*>(e);
                my_agent = payload_event->get_payload();
                notcute::log_debug(my_agent->toJson().serialize());
                redraw();
                return true;
            }
            default:
                break;
        }
        return Widget::on_event(e);
    }

    void draw(ncpp::Plane* p) {
        if (my_agent) {
            p->set_fg_palindex(255);
            p->printf(0, 0,"Account Id: %s", my_agent->getAccountId().c_str());
            p->printf(1, 0, "Symbol: %s", my_agent->getSymbol().c_str());
            p->printf(2, 0, "Credits: $%ld", my_agent->getCredits());
            p->printf(3, 0, "Headquarters: %s", my_agent->getHeadquarters().c_str());
            p->printf(4, 0, "Starting Faction: %s", my_agent->getStartingFaction().c_str());
            p->printf(5, 0, "Ship Count: %d", my_agent->getShipCount());
        }
    }

    ContentPane* get_content_pane() { return content_pane; }

private:
    std::shared_ptr<api::Agent> my_agent;
    api::AgentsApi api;
    MyAgentContentPane* content_pane = nullptr;
};

class EventLogEvent : public notcute::Event {
public:
    EventLogEvent(notcute::Widget* sender,
                  int type)
        : notcute::Event(sender,static_cast<notcute::Event::EventType>(type))
    {}
private:

};

class EventLogWidget : public notcute::Widget {
public:
    struct Event {
        std::function<void()> action;
    };
    using EventPtr = std::shared_ptr<Event>;

    EventLogWidget(Widget* parent = nullptr)
        :notcute::Widget(parent)
    {
        set_layout(new notcute::HBoxLayout);
        get_layout()->set_size(6, 0);
        get_layout()->set_behave(LAY_HFILL);
        set_focus_policy(notcute::FocusPolicy::FOCUS);
    }

    bool on_event(notcute::Event* e) override {
        switch(static_cast<sptr::EventType>(e->get_type())) {
            case sptr::EVENTLOG_EVENT: {
                EventLogEvent* event = static_cast<EventLogEvent*>(e);
                // EventPtr ep = event->get_event();
                return true;
            }
            default:
                break;
        }
        return false;
    }

    notcute::signal<void()> on_next_pane;
    notcute::signal<void()> on_prev_pane;

    std::queue<EventPtr> events;
};


class Dashboard : public notcute::Widget {
public:
    Dashboard(const sptr::User* user, Widget* parent = nullptr)
        : Widget(parent)
    {
        set_name("Dashboard");
        set_layout(new notcute::VBoxLayout);

        notcute::Widget* main_widget = new notcute::Widget(parent);
        main_widget->set_layout(new notcute::HBoxLayout);

        auto title_widget = new TitleWidget(this);
        title_widget->get_layout()->set_behave(LAY_TOP | LAY_HCENTER);
        get_layout()->add_widget(title_widget);

        scroll_area = new notcute::ScrollArea(nullptr, main_widget);
        scroll_area->get_layout()->set_behave(LAY_CENTER);

        panels = {
            .container = new notcute::Widget(this),
            .my_agent = new MyAgentWidget(user, this),
            .contracts = new ContractsListWidget(user, this),
            // .event_log = new EventLogWidget(this),
        };

        panels.my_agent_frame = notcute::FrameWidget::wrap(panels.my_agent);
        panels.contracts_frame = notcute::FrameWidget::wrap(panels.contracts);
        // panels.event_log_frame = notcute::FrameWidget::wrap(panels.event_log);

        panels.my_agent_frame->set_title(user->name);
        panels.contracts_frame->set_title("Contracts");
        // panels.event_log_frame->set_title("Event Log");

        panels.container->set_layout(new notcute::VBoxLayout);
        panel_content_container = new notcute::Widget(this);
        panel_content_container->set_layout(new notcute::VBoxLayout);
        // panel_content = new ContentPane(panel_content_container);
        // panel_content->set_layout(new notcute::VBoxLayout);
        //
        // panel_content_container->get_layout()->add_widgets({panel_content,
        //                                                     panels.event_log_frame});
        panels.container->get_layout()->set_size(0, 50);
        panels.container->get_layout()->set_behave(LAY_VFILL);
        panels.my_agent_frame->get_layout()->set_behave(LAY_HFILL | LAY_TOP);
        panels.contracts_frame->get_layout()->set_behave(LAY_HFILL | LAY_TOP);
        // panels.event_log_frame->get_layout()->set_behave(LAY_HFILL | LAY_BOTTOM);

        panels.container->get_layout()->add_widget(panels.my_agent_frame);
        panels.container->get_layout()->add_widget(panels.contracts_frame);

        panels.contracts->set_focus();

        panels.my_agent->set_name("my_agent");
        panels.my_agent_frame->set_name("my_agent_frame");
        panels.contracts->set_name("contracts");
        panels.contracts_frame->set_name("contracts_frame");

        // reparent(main_widget);
        scroll_area->set_content(panels.container);

        main_widget->get_layout()->add_widgets({scroll_area, panel_content_container});


        auto* controls_text = new notcute::TextWidget(" <l/h>: Next/Prev Panel, <j/k>: Scroll", this);
        // TODO: Why doesn't this margin work???? Temporary workaround by putting a space in the text string
        // controls_text->get_layout()->set_margins_ltrb(1,0,0,0);
        controls_text->get_layout()->set_behave(LAY_LEFT | LAY_BOTTOM);
        controls_text->get_plane()->set_fg_palindex(4);

        get_layout()->add_widget(main_widget);
        get_layout()->add_widget(controls_text);

        // connect_panel_to_content(panels.contracts, panel_content);
        // panels.contracts->set_content_pane(panel_content);

        setup_keyboard_pane_navigation();

        set_active_pane(panels.my_agent);
        scroll_area->set_focus();
    }

    void set_active_pane(ContentPaneDrawer* pd) {
        pd->set_focus();
        ContentPane* cp = pd->get_content_pane();

        if (panel_content_container->get_layout()->take(active_content_pane)) {
            notcute::log_debug("set active pane");
        }

        panel_content_container->get_layout()->add_widget(cp);
        active_content_pane = cp;
    }

    void setup_keyboard_pane_navigation() {
        auto connect_panes = [this](auto* widget, auto* prev, auto* next) {
            widget->on_next_pane.connect([this, next](){ 
                    set_active_pane(next);
                });
            widget->on_prev_pane.connect([this, prev](){
                    set_active_pane(prev);
                });
        };

        //            the panel         the next panel    the prev pane
        connect_panes(panels.my_agent, panels.contracts, panels.contracts);
        connect_panes(panels.contracts, panels.my_agent, panels.my_agent);
        // connect_panes(panels.event_log, panels.my_agent, panels.contracts);
    }

private:
    notcute::Widget* panel_content_container = nullptr;
    ContentPane* active_content_pane = nullptr;

    notcute::ScrollArea* scroll_area = nullptr;

    struct {
        notcute::Widget*      container = nullptr;
        MyAgentWidget*        my_agent = nullptr;
        notcute::FrameWidget* my_agent_frame = nullptr;
        ContractsListWidget*  contracts = nullptr;
        notcute::FrameWidget* contracts_frame = nullptr;
        EventLogWidget*       event_log = nullptr;
        notcute::FrameWidget* event_log_frame = nullptr;

    } panels;
};

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


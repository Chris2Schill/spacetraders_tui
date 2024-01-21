#pragma once

#include <notcute/frame_widget.hpp>
#include <CppRestOpenAPIClient/api/AgentsApi.h>

#include "sptr_api.h"
#include "events.h"

using Agent = std::shared_ptr<api::Agent>;

class MyAgentContentPane : public notcute::FrameWidget {
public:
    MyAgentContentPane(notcute::Widget* parent = nullptr)
        :notcute::FrameWidget(parent)
    {
        set_layout(new notcute::VBoxLayout);
        get_layout()->set_size(100,100);
        set_title("My Agent");
    }

    void draw(ncpp::Plane* p) {
        FrameWidget::draw(p);
        if (agent) {
            p->set_fg_palindex(255);
            p->printf(1, 1,"Account Id: %s", agent->getAccountId().c_str());
            p->printf(2, 1, "Symbol: %s", agent->getSymbol().c_str());
            p->printf(3, 1, "Credits: $%ld", agent->getCredits());
            p->printf(4, 1, "Headquarters: %s", agent->getHeadquarters().c_str());
            p->printf(5, 1, "Starting Faction: %s", agent->getStartingFaction().c_str());
            p->printf(6, 1, "Ship Count: %d", agent->getShipCount());
        }
    }

    void set_agent(Agent a)
    {
        agent = a;
        redraw();
    }

    Agent agent;
};

class MyAgentWidget : public notcute::FrameWidget {
public:
    using Agent = std::shared_ptr<api::Agent>;

    MyAgentWidget(const sptr::User* user, Widget* parent = nullptr)
        : notcute::FrameWidget(parent)
        , api(sptr::get_api_client())
    {
        new notcute::VBoxLayout(this);
        request_data();
        get_layout()->set_size(3, 20);
        get_layout()->set_behave(LAY_HFILL);
        set_title("My Agent");
        set_name("My Agent");
        content_pane = new MyAgentContentPane(this);
    }

    void request_data() {
        api.getMyAgent()
           .then([this](auto x){
                   API_ERROR_GUARD_START
                   auto agent = x.get()->getData();
                   auto event = new PayloadEvent(this, sptr::PAYLOAD_EVENT, agent);
                   notcute::EventLoop::get_instance()->post(event);
                   API_ERROR_GUARD_END
               });
    }

    bool on_event(notcute::Event* e) {
        switch(static_cast<sptr::EventType>(e->get_type())) {
            case sptr::PAYLOAD_EVENT: {
                auto payload_event = static_cast<PayloadEvent<Agent>*>(e);
                my_agent = payload_event->get_payload();
                notcute::log_debug(my_agent->toJson().serialize());
                content_pane->set_agent(my_agent);
                redraw();
                return true;
            }
            default:
                break;
        }
        return Widget::on_event(e);
    }

    void draw(ncpp::Plane* p) {
        FrameWidget::draw(p);
        if (my_agent) {
            p->set_fg_palindex(255);
            p->printf(1, 1,"%s", my_agent->getSymbol().c_str());
            std::string credits = "$" + std::to_string(my_agent->getCredits());
            p->set_fg_rgb8(0,100,0);
            p->putstr(1, p->get_dim_x()-credits.size()-1, credits.c_str());
        }
    }

    notcute::Widget* get_content_pane() { return content_pane; }

private:
    std::shared_ptr<api::Agent> my_agent;
    api::AgentsApi api;
    MyAgentContentPane* content_pane = nullptr;
};


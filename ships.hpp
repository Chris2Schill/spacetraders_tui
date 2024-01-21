#pragma once


#include <notcute/frame_widget.hpp>
#include <notcute/list_widget.hpp>
#include <notcute/text_widget.hpp>
#include <notcute/spacer.hpp>
#include <CppRestOpenAPIClient/api/FleetApi.h>
#include "sptr_api.h"
#include "events.h"
#include <notcute/colors.hpp>
#include "util.h"

using Ship = std::shared_ptr<api::Ship>;
using Ships = std::vector<Ship>;
using ShipListItem = notcute::ListItem_t<Ship>;


using ShipRequirements = std::shared_ptr<api::ShipRequirements>;
using ShipEngine = std::shared_ptr<api::ShipEngine>;
using ShipFrame = std::shared_ptr<api::ShipFrame>;
using ShipFuel = std::shared_ptr<api::ShipFuel>;
using ShipMount = std::shared_ptr<api::ShipMount>;
using ShipReactor = std::shared_ptr<api::ShipReactor>;

using Label = notcute::TextWidget;

namespace notcute {
    template<>
    inline std::string to_string<Ship>(const Ship& s) {
        return s->getSymbol() + " - " + s->getNav()->getWaypointSymbol() + " - "
             + s->getNav()->getStatus()->toJson().as_string();
    }
}


class ShipRequirementsWidget : public notcute::FrameWidget {
public:
    ShipRequirementsWidget(ShipRequirements ship_req, Widget* parent = nullptr)
        :FrameWidget(parent)
        , ship_req(ship_req)
    {
        set_layout(new notcute::VBoxLayout(5, 20));
        get_layout()->set_behave(LAY_HCENTER);
        set_title("Requirements");

        ui.container = new notcute::Widget(this);
        ui.container->set_layout(new notcute::VBoxLayout);
        ui.container->get_layout()->set_margins_ltrb(1,1,1,1);

        if (ship_req->getCrew() > 0) {
            ui.crew = new Label("crew: " + std::to_string(ship_req->getCrew()), ui.container);
            ui.container->get_layout()->add_widget(ui.crew);
        }

        if (ship_req->getPower() > 0) {
            ui.power = new Label("speed: " + std::to_string(ship_req->getPower()), ui.container);
            ui.container->get_layout()->add_widget(ui.power);
        }

        if (ship_req->getSlots() > 0) {
            ui.slots = new Label("slots: " + std::to_string(ship_req->getSlots()), ui.container);
            ui.container->get_layout()->add_widget(ui.slots);
        }

        get_layout()->add_widget(ui.container);
    }

private:
    struct ui{
        notcute::Widget* container;
        Label* crew;
        Label* power;
        Label* slots;
    }ui;
    ShipRequirements ship_req;
};

class ShipReactorWidget : public notcute::FrameWidget {
public:
    ShipReactorWidget(ShipReactor reactor, Widget* parent = nullptr)
        :FrameWidget(parent)
        , reactor(reactor)
    {
        set_layout(new notcute::VBoxLayout(5, 20));
        // get_layout()->set_behave(LAY_HCENTER);
        set_title("Reactor");

        ui.hbox = sptr::new_hbox(this);
        ui.hbox->get_layout()->set_margins_ltrb(1,1,1,1);

        ui.lcontainer = sptr::new_vbox(ui.hbox);
        ui.rcontainer = sptr::new_vbox(ui.hbox);

        ui.name = new Label(reactor->getName(), ui.lcontainer);
        ui.description = new Label(reactor->getDescription(), ui.lcontainer, LAY_LEFT);
        ui.description->get_layout()->set_height(2);
        ui.description->set_scrolling(true);
        ui.condition = new Label("condition: " + std::to_string(reactor->getCondition()), ui.lcontainer);
        ui.power_output = new Label("power output: " + std::to_string(reactor->getPowerOutput()), ui.lcontainer);
        ui.ship_req = new ShipRequirementsWidget(reactor->getRequirements(), ui.rcontainer);

        ui.lcontainer->get_layout()->add_widget(ui.name);
        ui.lcontainer->get_layout()->add_widget(ui.description);
        ui.lcontainer->get_layout()->add_widget(ui.condition);
        ui.lcontainer->get_layout()->add_widget(ui.power_output);
        ui.rcontainer->get_layout()->add_widget(ui.ship_req);

        ui.hbox->get_layout()->add_widget(ui.lcontainer);
        ui.hbox->get_layout()->add_widget(ui.rcontainer);

        get_layout()->add_widget(ui.hbox);
    }

private:
    struct ui{
        notcute::Widget* hbox;
        notcute::Widget* lcontainer;
        notcute::Widget* rcontainer;
        Label* name;
        Label* description;
        Label* condition;
        Label* power_output;
        ShipRequirementsWidget* ship_req;
    }ui;
    ShipReactor reactor;
};

class ShipFrameWidget : public notcute::FrameWidget {
public:
    ShipFrameWidget(ShipFrame ship_frame, Widget* parent = nullptr)
        :FrameWidget(parent)
        , ship_frame(ship_frame)
    {
        set_layout(new notcute::VBoxLayout);
        // get_layout()->set_behave(LAY_HCENTER);
        set_title("Frame");

        ui.hbox = sptr::new_hbox(this);
        ui.hbox->get_layout()->set_margins_ltrb(1,1,1,1);

        ui.lcontainer = sptr::new_vbox(ui.hbox);
        ui.rcontainer = sptr::new_vbox(ui.hbox);

        ui.name = new Label(ship_frame->getName(), ui.lcontainer);
        ui.description = new Label(ship_frame->getDescription(), ui.lcontainer, LAY_LEFT);
        ui.description->get_layout()->set_height(3);
        ui.description->set_scrolling(true);
        ui.condition = new Label("condition: " + std::to_string(ship_frame->getCondition()),ui.lcontainer);
        ui.fuel_capacity = new Label("fuel capacity: " + std::to_string(ship_frame->getFuelCapacity()),ui.lcontainer);
        ui.module_slots = new Label("module slots: " + std::to_string(ship_frame->getModuleSlots()),ui.lcontainer);
        ui.ship_req = new ShipRequirementsWidget(ship_frame->getRequirements(), ui.rcontainer);

        ui.lcontainer->get_layout()->add_widget(ui.name);
        ui.lcontainer->get_layout()->add_widget(ui.description);
        ui.lcontainer->get_layout()->add_spacer();
        ui.lcontainer->get_layout()->add_widget(ui.condition);
        ui.lcontainer->get_layout()->add_widget(ui.fuel_capacity);
        ui.lcontainer->get_layout()->add_widget(ui.module_slots);
        ui.rcontainer->get_layout()->add_widget(ui.ship_req);
        ui.hbox->get_layout()->add_widget(ui.lcontainer);
        ui.hbox->get_layout()->add_widget(ui.rcontainer);
        get_layout()->add_widget(ui.hbox);
    }

private:
    struct ui{
        notcute::Widget* hbox;
        notcute::Widget* lcontainer;
        notcute::Widget* rcontainer;
        Label* name;
        Label* description;
        Label* condition;
        Label* fuel_capacity;
        Label* module_slots;
        Label* mounting_points;
        ShipRequirementsWidget* ship_req;
    }ui;
    ShipFrame ship_frame;
};


class ShipEngineWidget : public notcute::FrameWidget {
public:
    ShipEngineWidget(ShipEngine engine, Widget* parent = nullptr)
        :FrameWidget(parent)
        , engine(engine)
    {
        set_layout(new notcute::VBoxLayout(5, 20));
        // get_layout()->set_behave(LAY_HCENTER);
        set_title("Engine");

        ui.hbox = sptr::new_hbox(this);
        ui.hbox->get_layout()->set_margins_ltrb(1,1,1,1);

        ui.lcontainer = sptr::new_vbox(ui.hbox);
        ui.rcontainer = sptr::new_vbox(ui.hbox);

        ui.name = new Label(engine->getName(), ui.lcontainer);
        ui.description = new Label(engine->getDescription(), ui.lcontainer, LAY_LEFT);
        ui.description->get_layout()->set_height(3);
        ui.description->set_scrolling(true);
        ui.speed = new Label("speed: " + std::to_string(engine->getSpeed()), ui.lcontainer);
        ui.ship_req = new ShipRequirementsWidget(engine->getRequirements(), ui.rcontainer);

        ui.lcontainer->get_layout()->add_widget(ui.name);
        ui.lcontainer->get_layout()->add_widget(ui.description);
        ui.lcontainer->get_layout()->add_widget(ui.speed);
        ui.rcontainer->get_layout()->add_widget(ui.ship_req);

        ui.hbox->get_layout()->add_widget(ui.lcontainer);
        ui.hbox->get_layout()->add_widget(ui.rcontainer);

        get_layout()->add_widget(ui.hbox);
    }

private:
    struct ui{
        notcute::Widget* hbox;
        notcute::Widget* lcontainer;
        notcute::Widget* rcontainer;
        Label* name;
        Label* description;
        Label* speed;
        ShipRequirementsWidget* ship_req;
    }ui;
    ShipEngine engine;
};

class ShipWidget : public notcute::FrameWidget {
public:
    ShipWidget(notcute::Widget* parent = nullptr)
        : notcute::FrameWidget(parent) {
        set_layout(new notcute::VBoxLayout);
        set_title("Ship");

        ui.container = new notcute::Widget(this);
        ui.container->set_layout(new notcute::VBoxLayout);
        ui.container->get_layout()->set_margins_ltrb(1,1,1,1);

        const int NUM_HBOXS = 1;
        for (int i = 0; i < NUM_HBOXS; ++i) {
            notcute::Widget* wrapper = new notcute::FrameWidget(ui.container);
            wrapper->set_layout(new notcute::HBoxLayout(1,0));
            wrapper->get_layout()->set_behave(LAY_HFILL);
            ui.hboxs.push_back(wrapper);
            ui.container->get_layout()->add_widget(wrapper);
        }

        ui.ship_name = new Label("SHIPNAME", ui.hboxs[0], LAY_LEFT);
        ui.faction = new Label("FACTION", ui.hboxs[0]);
        ui.role = new Label("ROLE", ui.hboxs[0], LAY_RIGHT);

        ui.hboxs[0]->get_layout()->add_widget(ui.ship_name);
        ui.hboxs[0]->get_layout()->add_widget(ui.faction);
        ui.hboxs[0]->get_layout()->add_widget(ui.role);

        get_layout()->add_widget(ui.container);
    }

    void set_ship(Ship s)
    {
        ship = s;
        auto pretty_json = sptr::pretty_json(ship->toJson().serialize());
        notcute::log_debug(pretty_json);

        ui.ship_name->set_text(ship->getSymbol());
        ui.role->set_text(ship->getRegistration()->getRole()->toJson().as_string());
        ui.faction->set_text(ship->getRegistration()->getFactionSymbol());


        if (ui.ship_frame) { ui.ship_frame->take_and_delete_later(); }
        ui.ship_frame = new ShipFrameWidget(ship->getFrame(), ui.container);
        ui.container->get_layout()->add_widget(ui.ship_frame);

        if (ui.engine) { ui.engine->take_and_delete_later(); }
        ui.engine = new ShipEngineWidget(ship->getEngine(), ui.container);
        ui.container->get_layout()->add_widget(ui.engine);


        if (ui.reactor) { ui.reactor->take_and_delete_later(); }
        ui.reactor = new ShipReactorWidget(ship->getReactor(), ui.container);
        ui.container->get_layout()->add_widget(ui.reactor);

        if (!ui.spacer) {ui.spacer = new notcute::Spacer(ui.container);}
        else {
            ui.spacer->take();
        }
        ui.container->get_layout()->add_widget(ui.spacer);

        redraw();
    }

private:
    struct ui
    {
        notcute::Widget* container;
        std::vector<notcute::Widget*> hboxs;
        Label* ship_name;
        Label* role;
        Label* faction;
        ShipFrameWidget* ship_frame;
        ShipEngineWidget* engine;
        ShipReactorWidget* reactor;
        notcute::Spacer* spacer;
    }ui;

    Ship ship = nullptr;
};

class MyShipsWidget : public notcute::ListWidget {
public:

    MyShipsWidget(notcute::Widget* parent = nullptr)
        :notcute::ListWidget(parent)
        ,api(sptr::get_api_client())
    {
        content_pane = new ShipWidget(this);

        request_data();
        get_layout()->set_size(6, 0);
        get_layout()->set_behave(LAY_HFILL);
        set_title("My Ships");
        set_name("My Ships");

        item_hovered.connect([this](notcute::ListItem* item){
                Ship ship = notcute::list_widget_item_t_get_item<Ship>(item);
                // notcute::log_debug("selected contract! " + contract->getId());
                content_pane->set_ship(ship);
            });
    }

    void request_data() {
        api.getMyShips({},{})
           .then([this](auto task){
                   API_ERROR_GUARD_START
                   auto ships = task.get()->getData();
                   auto event = new PayloadEvent(this, sptr::PAYLOAD_EVENT, ships);
                   notcute::EventLoop::get_instance()->post(event);
                   API_ERROR_GUARD_END
               });
    }

    bool on_event(notcute::Event* e) override {
        switch(static_cast<sptr::EventType>(e->get_type())) {
            case sptr::PAYLOAD_EVENT: {
                auto payload_event = static_cast<PayloadEvent<Ships>*>(e);
                ships = payload_event->get_payload();
                clear();
                for (Ship c : ships) {
                    // notcute::log_debug(c->toJson().serialize());
                    auto item = new ShipListItem(c);
                    add_item(item);
                }
                return true;
            }
            default:
                break;
        }

        return Widget::on_event(e);
    }

    Widget* get_content_pane() const { return content_pane; }

    ShipWidget* content_pane = nullptr;

    api::FleetApi api;
    Ships ships;
};

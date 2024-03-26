#pragma once

#include <memory>

#include <CppRestOpenAPIClient/api/SystemsApi.h>

#include <ncpp/Reel.hh>
#include <ncpp/Tablet.hh>
#include <ncpp/Selector.hh>
#include <notcurses/notcurses.h>
#include <notcurses/nckeys.h>
#include <nlohmann/json.hpp>

#include "framed_plane.h"
#include "panel.h"

inline int draw_waypoint(nctablet* t, bool drawFromtop) {
    // ncpp::Tablet t(t, get_notcurses());

    ncpp::NcTablet* tablet = ncpp::NcTablet::map_tablet(t);
    api::Waypoint* wp = tablet->get_userptr<api::Waypoint>();

    ncpp::Plane* plane = tablet->get_plane();
    // auto text = fmt::format("{}                   {}", wp->getSymbol());
    // plane->printf(0, 1, text.c_str());

    plane->putstr(0, 1, fmt::format("{}", wp->getSymbol()).c_str());
    plane->putstr(1, 1, fmt::format("Faction: {}", (int)wp->getFaction()->getSymbol()->getValue()).c_str());
    plane->putstr(2, 1, fmt::format("X: {}", wp->getX()).c_str());
    plane->putstr(3, 1, fmt::format("Y: {}", wp->getY()).c_str());
    // putstr("|_______________________________________|");
    // putstr("                                                 ");
    // log_debug(text);
    
    return 4;
}


class WaypointsReel : public Panel {
public:
    WaypointsReel() {
        auto plane = ncpp::Plane(25, 100, 0, 51);
        ncpp::NcReel::default_options.borderchan = 0xFFFFFFFF;
        reel = new ncpp::NcReel(plane);
    }


    void refresh() override {
        static api::SystemsApi api(sptr::get_api_client());

        api.getSystemWaypoints("X1-MT7", {}, 50, {}, {} )
           .then([this](auto task){
                   std::scoped_lock lock(mtx);
                   waypoints = task.get()->getData();

                   for (auto w : waypoints) {
                       auto data = nlohmann::json::parse(w->toJson().serialize());
                       log_debug(data.dump(2));
                   }
                   dirty = true;
               });
    }

    bool offer_input(ncinput* ni) {
        switch(ni->id) {
            case 'j':
                reel->next();
                reel->redraw();
                return true;
                break;
            case 'k':
                reel->prev();
                reel->redraw();
                return true;
                break;

        }
        return false;
    }

    void update() override {

        if (dirty) {
            {
                std::scoped_lock lock(mtx);
                // erase();
                // reel->del
                for (auto t : tablets) {
                    reel->del(t);
                }
                tablets.clear();
                for (auto w : waypoints) {
                    ncpp::NcTablet* tablet = reel->add(NULL, NULL, draw_waypoint, w.get());
                    tablets.push_back(tablet);


                    // auto data = nlohmann::json::parse(w->toJson().serialize()).dump(2);
                    // auto lines = tokenize(data, '\n');
                    // for (auto& line : lines) {
                    //     putstr(line);
                    // }
                }
            }
            dirty = false;
        }
    }

    ncpp::NcReel* reel;
    std::vector<std::shared_ptr<api::Waypoint>> waypoints;
    std::vector<ncpp::NcTablet*> tablets;
    bool dirty = true;
};

class PanelManager {
public:
};

class WaypointsPanel : public FramedScrollTextPlane {
public:
    WaypointsPanel()
        : FramedScrollTextPlane(25, 100, 0, 51)
    {
        // contents->set_scrolling(true);
    }

    void put_waypoint(std::shared_ptr<api::Waypoint> waypoint) {
        putstr(fmt::format("|-{}----------------------{}",
                waypoint->getSymbol().c_str(),
                (int)waypoint->getFaction()->getSymbol()->getValue()));

        putstr("|Location:");
        putstr(fmt::format("|X: {}", waypoint->getX()));
        putstr(fmt::format("|Y: {}", waypoint->getY()));
        putstr("|_______________________________________|");
        putstr("                                                 ");
                // std::to_string(waypoint->getFaction()->getSymbol()->getValue()));
    }

    void refresh() override {
        static api::SystemsApi api(sptr::get_api_client());

        api.getSystemWaypoints("X1-MT7", {}, {}, {}, {} )
           .then([this](auto task){
                   std::scoped_lock lock(mtx);
                   waypoints = task.get()->getData();

                   for (auto w : waypoints) {
                       auto data = nlohmann::json::parse(w->toJson().serialize());
                       log_debug(data.dump(2));
                   }
                   dirty = true;
               });
    }

    void update() override {

        if (dirty) {
            {
                std::scoped_lock lock(mtx);
                erase();
                for (auto w : waypoints) {
                    put_waypoint(w);
                    // auto data = nlohmann::json::parse(w->toJson().serialize()).dump(2);
                    // auto lines = tokenize(data, '\n');
                    // for (auto& line : lines) {
                    //     putstr(line);
                    // }
                }
            }
        }


        // if (is_selected) {
        //     contents->set_fg_palindex(1);
        // }

        // contents->cursor_move(1,1);
        contents->set_fg_palindex(255);
        FramedScrollTextPlane::update();

        // Todo move to constructor
        set_title("Waypoints");
        dirty = false;
        // plane->perimeter_rounded(0, chans, 0xF0);
    }
private:
    std::vector<std::shared_ptr<api::Waypoint>> waypoints;
    bool dirty = true;
};

inline void draw_waypoint_trait_tab(nctab* t, ncplane* ncp, void* userptr) {
    ncplane_erase(ncp);
    ncplane_resize_simple(ncp, 10, 50);
    ncplane_set_scrolling(ncp, true);

    api::WaypointTrait* trait = static_cast<api::WaypointTrait*>(userptr);
    ncplane_puttext(ncp, 1, NCALIGN_LEFT, trait->getDescription().c_str(), NULL);
}

class WaypointsPanel2 : public FramedPlane {
    ncpp::Selector* itemList = nullptr;
    ncpp::Plane*    itemContents = nullptr;
    nctabbed*       tabs = nullptr;
public:
    WaypointsPanel2()
        : FramedPlane(25, 100, 0, 51)
        , api(sptr::get_api_client())
    {
        renew();
        itemContents = new ncpp::Plane(contents, 25, 30, 0, 15);

    }
    api::SystemsApi api;

    void refresh() override {

        utility::string_t traits("SHIPYARD");//std::make_shared<util>();

        api.getSystemWaypoints("X1-MT7", {}, {}, {}, {traits} )
           .then([this](auto task){
                   std::scoped_lock lock(mtx);
                   waypoints = task.get()->getData();

                   for (auto w : waypoints) {
                       auto data = nlohmann::json::parse(w->toJson().serialize());
                       log_debug(data.dump(2));
                   }
                   dirty = true;
               });
    }


    void renew_tabs() {
        nctabbed_destroy(tabs);
        nctabbed_options topts = {
            .selchan = NCCHANNELS_INITIALIZER(0, 255, 0, 0, 0, 0),
            .hdrchan = NCCHANNELS_INITIALIZER(255, 0, 0, 60, 60, 60),
            .sepchan = NCCHANNELS_INITIALIZER(255, 255, 255, 100, 100, 100),
            .separator = "|",
        };
        auto tabPlane = new ncpp::Plane(contents, 25, 150, 10, 15);
        tabs = nctabbed_create(tabPlane->to_ncplane(), &topts);
    }

    ncselector_options sopts = {};
    void renew() {
        delete itemList;
        auto p = ncpp::Plane(contents, 25, 15, 0, 0);

        sopts.opchannels = NCCHANNELS_INITIALIZER(0xe0, 0x80, 0x40, 0, 0, 0);
        sopts.descchannels = NCCHANNELS_INITIALIZER(0x80, 0xe0, 0x40, 0, 0, 0);
        sopts.footchannels = NCCHANNELS_INITIALIZER(0xe0, 0, 0x40, 0x20, 0, 0);
        sopts.titlechannels = NCCHANNELS_INITIALIZER(0xff, 0xff, 0x80, 0, 0, 0x20);
        itemList = new ncpp::Selector(p, &sopts);

        renew_tabs();
    }

    void update() override {

        if (dirty) {
            renew();

            {
                std::scoped_lock lock(mtx);
                for (auto w : waypoints) {
                    ncselector_item i;
                    i.option = w->getSymbol().c_str();
                    itemList->additem(&i);
                }
                dirty = false;
            }
        }

        update_frame();
        contents->set_fg_palindex(255);
        set_title("Waypoints");
    }

    void draw_selected_waypoint() {
        std::shared_ptr<api::Waypoint> wp = nullptr;
        const char* option = itemList->get_selected();
        for (auto w : waypoints) {
            if (w->getSymbol() == option) {
                wp = w;
                break;
            }
        }

        itemContents->erase();
        if (wp) {
            itemContents->putstr(1, 1, fmt::format("{}    {}",
                        wp->getSymbol(),
                        wp->getType()->toJson().as_string().c_str()
                        ).c_str());

            itemContents->putstr(2, 1, fmt::format("Faction:{}", 
                        (int)wp->getFaction()->getSymbol()->getValue()).c_str());
            itemContents->putstr(3, 1, fmt::format("Coordinates: ({},{}) ", wp->getX(), wp->getY()).c_str());
            if (wp->isIsUnderConstruction()) {
                itemContents->putstr(4, 1, "Under Construction");
            }

            renew_tabs();
            for (auto t : wp->getTraits()) {
                std::string name = t->getSymbol()->toJson().as_string();
                nctabbed_add(tabs, NULL, NULL, draw_waypoint_trait_tab, name.c_str(), t.get());
            }
        }
    }

    std::shared_ptr<api::Shipyard> shipyard = nullptr;

    bool offer_input(ncinput* ni) override {

        if (waypoint_selected) {
            switch (ni->id) {
                case ',':
                case 'l':
                    nctabbed_next(tabs);
                    nctabbed_redraw(tabs);
                    return true;
                    break;
                case '.':
                case 'h':
                    nctabbed_prev(tabs);
                    nctabbed_redraw(tabs);
                    return true;
                    break;
                case NCKEY_ENTER:
                    api.getShipyard(waypoint_selected->getSystemSymbol(), waypoint_selected->getSymbol())
                       .then([this](auto task) {
                               std::scoped_lock lock(mtx);
                               shipyard = task.get()->getData();
                               log_debug(shipyard->toJson().serialize());
                           });

                    break;
                case NCKEY_ESC:
                    waypoint_selected = nullptr;
                    break;
            }

            return true;
        }

        switch (ni->id) {
            case 'j':
                itemList->nextitem();
                draw_selected_waypoint();
                nctabbed_redraw(tabs);
                return true;
                break;
            case 'k':
                itemList->previtem();
                draw_selected_waypoint();
                nctabbed_redraw(tabs);
                return true;
                break;
            case NCKEY_ENTER:
                log_debug("enter selected");

                const char* selwaypoint = itemList->get_selected();
                for (auto wp : waypoints) {
                    if (wp->getSymbol() ==  selwaypoint) {
                        waypoint_selected = wp;
                    }
                }
                nctabbed_redraw(tabs);
                sopts.boxchannels = NCCHANNELS_INITIALIZER(0x20, 0xe0, 0x40, 0x20, 0x20, 0x20);
                return true;
                break;
        }
        return false;
    }
private:
    std::vector<std::shared_ptr<api::Waypoint>> waypoints;
    bool dirty = true;
    std::shared_ptr<api::Waypoint> waypoint_selected = nullptr;
};

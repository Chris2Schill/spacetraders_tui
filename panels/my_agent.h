#pragma once

#include <CppRestOpenAPIClient/api/AgentsApi.h>
#include <ncfw/context.hpp>
#include "../sptr_api.h"
#include "framed_plane.h"


class MyAgentPanel : public FramedContext {
public:
    MyAgentPanel(ncfw::Context* ctx, ncplane_options* opts = ncfw::Context::default_options())
        : FramedContext(ctx, opts)
        ,api(sptr::get_api_client())
    { refresh(); }

    void refresh() override {
        api.getMyAgent()
           .then([this](auto x){
                   std::scoped_lock lock(mtx);
                   my_agent = x.get()->getData();
                   log_debug(my_agent->toJson().serialize());
               });
    }

    void draw_subcontent(ncfw::Context* subcontext) {
        subcontext->erase();
    }

    void update() override {
        erase();
        update_frame();

        // update_frame();

        set_fg_palindex(255);
        {
            std::scoped_lock lock(mtx);
            if (my_agent) {
                printf(1, 1,"Account Id: %s", my_agent->getAccountId().c_str());
                printf(2, 1, "Symbol: %s", my_agent->getSymbol().c_str());
                printf(3, 1, "Credits: $%ld", my_agent->getCredits());
                printf(4, 1, "Headquarters: %s", my_agent->getHeadquarters().c_str());
                printf(5, 1, "Starting Faction: %s", my_agent->getStartingFaction().c_str());
                printf(6, 1, "Ship Count: %d", my_agent->getShipCount());
                set_title(my_agent->getSymbol());
            }
        }
    }
private:
    std::shared_ptr<api::Agent> my_agent;
    api::AgentsApi api;
};

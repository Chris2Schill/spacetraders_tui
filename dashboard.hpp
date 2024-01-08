#pragma once

#include <notcurses/notcurses.h>
#include <ncfw/context.hpp>
#include <ncfw/layout.hpp>
#include <ncfw/framed_context.hpp>
#include <ncfw/event_bus.h>
#include "panels/my_agent.h"
#include "panels/contracts_panel.h"
#include "help_menu.hpp"

class Dashboard : public ncfw::Context {
public:

    template<typename T>
    auto draw_subcontent(T* ctx) {
        return [this,ctx](bool focused) {
            if (focused) {
                ctx->draw_subcontent(sub_content);
            }
        };
    }

    Dashboard()
    {
        using namespace ncfw::Align;

        ncplane_options popts = *ncfw::Context::default_options();
        popts.rows = 10;
        popts.cols = 40;

        auto toplevelVLayout = new ncfw::VerticalLayout(this);
        toplevelVLayout->debug_name = "main_horiz_container";
        toplevelVLayout->set_focusable(true);


        horizontalLayout = new ncfw::HorizontalLayout(toplevelVLayout);
        horizontalLayout->debug_name = "main_horiz_container";
        horizontalLayout->set_focusable(true);
        horizontalLayout->set_alignment(ncfw::Align::Left);



        verticalLayout = new ncfw::VerticalLayout(horizontalLayout, &popts);
        verticalLayout->set_focusable(true);
        verticalLayout->debug_name = "top_level_items";
        //TODO: Why do i have to set ALign left for nested layouts to center them?
        verticalLayout->set_alignment(ncfw::Align::Left);

        sub_content = new ncfw::FramedContext(horizontalLayout);


        auto my_agent = new MyAgentPanel(verticalLayout, &popts);
        my_agent->set_focusable(true);
        verticalLayout->add(my_agent);

        auto contracts = new ContractsPanel(verticalLayout, &popts);
        // contracts->resize(10,50);
        contracts->set_focusable(true);
        verticalLayout->add(contracts);
        // verticalLayout->add(new ContractPanel(verticalLayout, &popts));


        sub_content->resize(verticalLayout->get_content_height(),
                            verticalLayout->get_content_width());
        sub_content->update_frame();

        horizontalLayout->add(verticalLayout);
        horizontalLayout->add(sub_content);


        my_agent->focused_state_changed.connect(draw_subcontent(my_agent));
        contracts->focused_state_changed.connect(draw_subcontent(contracts));
        contracts->data_changed.connect([=](){contracts->draw_subcontent(contracts);});

        horizontalLayout->set_focused_context(verticalLayout);
        // Details context
        // ncfw::cover_plane(detailsCtx);
        // horizontalLayout->add(detailsCtx);
        // auto test = new ncfw::Text("BOOOOOIIII", this);
        // ncfw::center_context(this, test);
        // horizontalLayout->add(test);

        toplevelVLayout->add(horizontalLayout);
        auto controls = new ncfw::Text("l/h: next/prev panel, j/k: scroll up/down, <enter>: enter context", toplevelVLayout);
        toplevelVLayout->add(controls);
        // controls->set_bg_palindex(3);
        // controls->set_text("l/h: next/prev panel, j/k: scroll up/down, <enter>: enter context");
    }

    void refresh() override {
        horizontalLayout->refresh();
    }

    bool offer_input(ncinput* ni) override {
        switch(ni->id) {
            case NCKEY_ESC:
                EVENT_POST(ncfw::ChangeContext{ncfw::CONTEXT_MAIN_MENU});
                return true;
            case '?':
                EVENT_POST(ShowHelpMenu{this,[](HelpMenu* ctx) {
                        ctx->erase();
                        // ctx->update_frame();
                        // ctx->perimeter_double(0,0,0);
                        // ctx->set_scrolling(true);
                        ctx->home();
                        for (int i = 0; i < ctx->get_content_height(); ++i) {
                            ncplane_puttext(ctx->to_ncplane(), -1, NCALIGN_LEFT, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", nullptr);

                        }
                    }});
                return true;
        }
        return horizontalLayout->offer_input(ni);
    }

    void update() override {
        horizontalLayout->update(); 
    }

private:
    ncfw::HorizontalLayout* horizontalLayout;
    ncfw::VerticalLayout*   verticalLayout;
    ncfw::FramedContext*    sub_content;
};

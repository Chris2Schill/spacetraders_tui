#pragma once

#include <ncfw/context.hpp>
#include <ncfw/layout.hpp>
#include <ncfw/framed_context.hpp>
#include "panels/m

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
        popts.cols = 50;

        horizontalLayout = new ncfw::HorizontalLayout(this);
        horizontalLayout->debug_name = "main_horiz_container";
        horizontalLayout->set_focusable(true);
        horizontalLayout->resize(get_content_height(), get_content_width());



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

    }


    void refresh() override {
        horizontalLayout->refresh();
    }

    bool offer_input(ncinput* ni) override {
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

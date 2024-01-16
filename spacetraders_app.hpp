#pragma once

#include <thread>

#include <notcute/logger.hpp>
#include <ncfw/notcurses_app.h>
// #include <ncfw/framed_context.hpp>
// #include <ncfw/layout.hpp>
// #include <ncfw/logger.h>
// #include <ncfw/context.hpp>
#include <boost/signals2.hpp>
#include "panels.h"
#include "main_menu.hpp"
#include "dashboard.hpp"
#include "help_menu.hpp"



class SpaceTradersApplication : public ncfw::Application {
public:


    SpaceTradersApplication(const std::string& name)
        : ncfw::Application(name)
        // , help_menu(new ncfw::Context())
    {
        notcute::Renderer* renderer = notcute::Renderer::get_instance();
        notcute::Size term = renderer->get_term_size();
        auto main_menu = new MainMenu2(term.height, term.width);


        main_menu->user_selected.connect([](const sptr::User& user){ 
                // delete contexts[ncfw::CONTEXT_DASHBOARD];
                // contexts[ncfw::CONTEXT_DASHBOARD] = new Dashboard();
                // context = contexts[ncfw::CONTEXT_DASHBOARD];
                log_debug("user selected " + user.name + ", token = " + user.token);
            });

        main_menu->show();
        // contexts[ncfw::CONTEXT_MAIN_MENU] = main_menu;
        //
        //
        // context = contexts[ncfw::CONTEXT_MAIN_MENU];
        // test_layouts();
    }

    void draw_text(int align) {
        std::string text = "SHIZZMAKER";

        ncfw::VerticalLayout* pile = new ncfw::VerticalLayout();
        pile->set_alignment(align);
        pile->add(new ncfw::Text(text,pile));

        pile->show();

        std::this_thread::sleep_for(std::chrono::seconds(1));
        delete pile;
    }

    // HelpMenu help_menu;
    // void test_layouts() {
    //     using namespace ncfw::Align;
    //     draw_text(Top|Left);
    //     draw_text(Top|HCenter);
    //     draw_text(Top|Right);
    //     draw_text(VCenter|Left);
    //     draw_text(VCenter|HCenter);
    //     draw_text(VCenter|Right);
    //     draw_text(Bottom|Left);
    //     draw_text(Bottom|HCenter);
    //     draw_text(Bottom|Right);
    //     // Vertical Layout Left
    //     {
    //         ncfw::VerticalLayout* ctx = new ncfw::VerticalLayout();
    //         ctx->set_alignment(ncfw::Align::Top);
    //
    //         contexts[ncfw::CONTEXT_MAIN_MENU] = ctx;
    //         context = ctx;
    //
    //         ncplane_options popts = *ncfw::Context::default_options();
    //         popts.cols = 24;
    //         popts.rows = 6;
    //
    //         ctx->add(new ncfw::Text("SPACETRADERS", ctx));
    //         auto mainmenu = new ncfw::Selector(ctx, &popts);
    //         mainmenu->add_menu_item("CONTINUE", [](){ EVENT_POST(ncfw::ChangeContext{ncfw::CONTEXT_DASHBOARD});});
    //         mainmenu->add_menu_item("REGISTER NEW AGENT", [](){ EVENT_POST(ncfw::ChangeContext{ncfw::CONTEXT_DASHBOARD});});
    //         ctx->add(mainmenu, ncfw::Context::FOCUSED);
    //         ctx->show();
    //         std::this_thread::sleep_for(std::chrono::seconds(1));
    //
    //         delete ctx;
    //     }
    //
    //     // Vertical Layout Center
    //     {
    //         ncfw::VerticalLayout* ctx = new ncfw::VerticalLayout();
    //         ctx->set_alignment(ncfw::Align::VCenter);
    //
    //         contexts[ncfw::CONTEXT_MAIN_MENU] = ctx;
    //         context = ctx;
    //
    //         ncplane_options popts = *ncfw::Context::default_options();
    //         popts.cols = 24;
    //         popts.rows = 6;
    //
    //         ctx->add(new ncfw::Text("SPACETRADERS", ctx));
    //         auto mainmenu = new ncfw::Selector(ctx, &popts);
    //         mainmenu->add_menu_item("CONTINUE", [](){ EVENT_POST(ncfw::ChangeContext{ncfw::CONTEXT_DASHBOARD});});
    //         mainmenu->add_menu_item("REGISTER NEW AGENT", [](){ EVENT_POST(ncfw::ChangeContext{ncfw::CONTEXT_DASHBOARD});});
    //         ctx->add(mainmenu, ncfw::Context::FOCUSED);
    //         ctx->show();
    //         std::this_thread::sleep_for(std::chrono::seconds(1));
    //
    //         delete ctx;
    //     }
    //
    //
    //     // Horizontal Layout Left
    //     {
    //         ncfw::HorizontalLayout* ctx = new ncfw::HorizontalLayout();
    //         ctx->set_alignment(ncfw::Align::Left);
    //
    //         contexts[ncfw::CONTEXT_MAIN_MENU] = ctx;
    //         context = ctx;
    //
    //         ncplane_options popts = *ncfw::Context::default_options();
    //         popts.cols = 24;
    //         popts.rows = 6;
    //
    //         ctx->add(new ncfw::Text("SPACETRADERS", ctx));
    //         auto mainmenu = new ncfw::Selector(ctx, &popts);
    //         mainmenu->add_menu_item("CONTINUE", [](){ EVENT_POST(ncfw::ChangeContext{ncfw::CONTEXT_DASHBOARD});});
    //         mainmenu->add_menu_item("REGISTER NEW AGENT", [](){ EVENT_POST(ncfw::ChangeContext{ncfw::CONTEXT_DASHBOARD});});
    //         ctx->add(mainmenu, ncfw::Context::FOCUSED);
    //         ctx->show();
    //         std::this_thread::sleep_for(std::chrono::seconds(1));
    //
    //         delete ctx;
    //     }
    //
    //     // Horizontal Layout Center
    //     {
    //         ncfw::HorizontalLayout* ctx = new ncfw::HorizontalLayout();
    //         ctx->set_alignment(ncfw::Align::HCenter);
    //
    //         contexts[ncfw::CONTEXT_MAIN_MENU] = ctx;
    //         context = ctx;
    //
    //         ncplane_options popts = *ncfw::Context::default_options();
    //         popts.cols = 24;
    //         popts.rows = 6;
    //
    //         ctx->add(new ncfw::Text("SPACETRADERS", ctx));
    //         auto mainmenu = new ncfw::Selector(ctx, &popts);
    //         mainmenu->add_menu_item("CONTINUE", [](){ EVENT_POST(ncfw::ChangeContext{ncfw::CONTEXT_DASHBOARD});});
    //         mainmenu->add_menu_item("REGISTER NEW AGENT", [](){ EVENT_POST(ncfw::ChangeContext{ncfw::CONTEXT_DASHBOARD});});
    //         ctx->add(mainmenu, ncfw::Context::FOCUSED);
    //         ctx->show();
    //         std::this_thread::sleep_for(std::chrono::seconds(1));
    //
    //         delete ctx;
    //     }
    //
    //     // Vertical Layout nested in Horiz Layout (Left,Left)
    //     {
    //         ncfw::HorizontalLayout* ctx = new ncfw::HorizontalLayout();
    //         ctx->debug_name = "outer layout (horiz)";
    //         ctx->set_alignment(ncfw::Align::Left);
    //
    //         for (int i = 0; i < 2; ++i) {
    //             ncplane_options popts = *ncfw::Context::default_options();
    //             popts.rows = 10;
    //             popts.cols = 50;
    //
    //             ncfw::VerticalLayout* ctx2 = new ncfw::VerticalLayout(ctx, &popts);
    //             ctx2->set_alignment(ncfw::Align::Left);
    //             ctx2->debug_name = "inner layout (vlayout)";
    //
    //             for (int j = 0; j < 4; ++j) {
    //                 // auto ctx3 = new ncfw::Context(ctx2, &popts);
    //                 // ncfw::cover_plane(ctx3);
    //                 // ctx2->add(ctx3);
    //                 ctx2->add(new MyAgentPanel(ctx2, &popts));
    //             }
    //             // ctx2->add(new MyAgentPanel(ctx2, &popts));
    //             // ctx2->add(new MyAgentPanel(ctx2, &popts));
    //             // ctx2->add(new MyAgentPanel(ctx2, &popts));
    //             ctx->add(ctx2);
    //             log_debug(fmt::format("added 4 contexts to vlayout, contentHeightWidth={},{}", ctx2->get_content_height(), ctx2->get_content_width()));
    //         }
    //         ctx->show();
    //         std::this_thread::sleep_for(std::chrono::seconds(1));
    //         delete ctx;
    //     }
    //
    //     // Vertical Layout nested in Horiz Layout (Left,Center)
    //     {
    //         ncfw::HorizontalLayout* ctx = new ncfw::HorizontalLayout();
    //         ctx->debug_name = "outer layout (horiz)";
    //         ctx->set_alignment(ncfw::Align::Left);
    //
    //         for (int i = 0; i < 2; ++i) {
    //             ncplane_options popts = *ncfw::Context::default_options();
    //             popts.rows = 10;
    //             popts.cols = 50;
    //
    //             ncfw::VerticalLayout* ctx2 = new ncfw::VerticalLayout(ctx, &popts);
    //             ctx2->set_alignment(ncfw::Align::VCenter);
    //             ctx2->debug_name = "inner layout (vlayout)";
    //
    //             for (int j = 0; j < 4; ++j) {
    //                 // auto ctx3 = new ncfw::Context(ctx2, &popts);
    //                 // ncfw::cover_plane(ctx3);
    //                 // ctx2->add(ctx3);
    //                 ctx2->add(new MyAgentPanel(ctx2, &popts));
    //             }
    //             // ctx2->add(new MyAgentPanel(ctx2, &popts));
    //             // ctx2->add(new MyAgentPanel(ctx2, &popts));
    //             // ctx2->add(new MyAgentPanel(ctx2, &popts));
    //             ctx->add(ctx2);
    //             log_debug(fmt::format("added 4 contexts to vlayout, contentHeightWidth={},{}", ctx2->get_content_height(), ctx2->get_content_width()));
    //         }
    //         ctx->show();
    //         std::this_thread::sleep_for(std::chrono::seconds(1));
    //         delete ctx;
    //     }
    //
    // }

};

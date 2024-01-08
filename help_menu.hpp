#pragma once

#include <functional>

#include <ncfw/layout.hpp>
#include <ncfw/event_bus.h>
#include <ncfw/framed_context.hpp>

class HelpMenu;

struct ShowHelpMenu {
    ncfw::Context* ctx;
    std::function<void(HelpMenu*)> draw;
};

class HelpMenu : public ncfw::FramedContext {
    public:
    HelpMenu(ncfw::Context* ctx)
        : ncfw::FramedContext(ctx, new ncplane_options{.rows = 50, .cols = 50})
    {
        resize(50,50);
        resize_realign();
        update_frame();
        EVENT_SUBSCRIBE<ShowHelpMenu>(this, &HelpMenu::show_menu);
    }

    void show_menu(const ShowHelpMenu& e) {
        log_debug("show_menu");
        e.draw(this);
        ncfw::center_context(e.ctx, this);
        reparent(e.ctx);
        // move_top();
        show();
        ncpp::NotCurses::get_instance().get(true);
        reparent(nullptr);
    }
};


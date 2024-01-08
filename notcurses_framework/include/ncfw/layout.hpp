#pragma once
#include <sstream>

#include "context.hpp"
#include "ring_index.hpp"
#include "logger.h"

namespace ncfw {


void cover_plane(ncfw::Context* p) {
    p->set_scrolling(true);
    for (int i = 0; i < 5000; ++i) {
        p->putstr("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    }
    // auto chans = NCCHANNEL_INITIALIZER(0, 255, 0);
    // p->perimeter_rounded(0, chans, 0);
}

void draw_center_lines(ncfw::Context* ctx) {
    ncplane_options hopts {
        .y = (int)ctx->get_dim_y()/2,
        .x = 0,
        .rows = 1,
        .cols = ctx->get_dim_x(),
    };
    ncfw::Context* horiz_line = new ncfw::Context(ctx, &hopts);
    for (int i = 0; i < ctx->get_dim_x(); ++i) {
        horiz_line->putc("-");
    }

    ncplane_options vopts {
        .y = 0,
        .x = (int)ctx->get_dim_x()/2,
        .rows = ctx->get_dim_y(),
        .cols = 1,
    };
    ncfw::Context* vert_line = new ncfw::Context(ctx, &vopts);
    for (int i = 0; i < ctx->get_dim_x(); ++i) {
        vert_line->putc(i, 0, "|");
    }
}

void draw_at_y_x(ncfw::Context* p) {
    // p->set_scrolling(true);
    // for (int i = 0; i < 5000; ++i) {
    //     p->putstr("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    // }

    int py,px;
    p->get_yx(&py, &px);
    ncplane_options opts {
        .y = py,
        .x = px,
        .rows = (unsigned)p->get_content_height(),
        .cols = (unsigned)p->get_content_width(),
    };
    ncfw::Context* c = new ncfw::Context(p, &opts);

    // int cy,cx;
    // c->get_yx(&cy, &cx);

    // c->putstr(cy,cx, "z");
    c->set_scrolling(true);
    c->home();
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            // unsigned y = c->cursor_y();
            // log_debug(fmt::format("Y = {}", y));
            // std::string s = std::to_string(j);
            c->putstr("*");
        }
    }
    // c->move(1,1);
    
    // auto chans = NCCHANNEL_INITIALIZER(0, 255, 0);
    // p->perimeter_rounded(0, chans, 0);
}


class Layout : public Context {
public:
    using Context::Context;

    void focus_next() {

        if (get_focusable()) {
            do {
                focused_context->set_focused(false);
                curr_context_idx.next();
                focused_context = contexts[curr_context_idx.get_value()];
                focused_context->set_focused(true);
            }
            while (!focused_context->get_focusable());
        }
    }

    void focus_prev() {

        if (get_focusable()) {
            do {
                focused_context->set_focused(false);
                curr_context_idx.prev();
                focused_context = contexts[curr_context_idx.get_value()];
                focused_context->set_focused(true);
            }
            while (!focused_context->get_focusable());
        }
    }

    void add(Context* p, eFocus focused = Context::NOT_FOCUSED) {
        contexts.push_back(p);
        curr_context_idx.set_max(contexts.size()-1);

        if (focused == Context::FOCUSED) {
            p->set_focusable(true);
        }

        if (p->get_focusable()) {
            set_focusable(true);
        }

        if (get_focusable()) {
            if ((!focused_context && p->get_focusable()) || focused == Context::FOCUSED) {
                set_focused_context(p);
            }
        }

        // p->reparent(this);

        if (auto layout = dynamic_cast<ncfw::Layout*>(p)) {
            layout->resize(get_content_height(), get_content_width());
            resize_realign();
        }
        reformat();

    }

    void set_focused_context(Context* ctx) {
        for (auto c : contexts) {
            c->set_focused(false);
        }
        ctx->set_focused(true);
        focused_context = ctx;
    }

    void update() override {
        erase();
        for (auto c : contexts) {
            c->update();
        }
        // auto chans = NCCHANNEL_INITIALIZER(100, 0, 0);
        // perimeter_rounded(0, chans, 0);
    }

    void refresh() override {
        for (auto c : contexts) {
            c->refresh();
        }
    }

    bool offer_input(ncinput* ni) override {
        if (focused_context) {
            bool handled = focused_context->offer_input(ni);
            if (handled) { log_debug("handled by focused obj"); return true; }
        }

        switch(ni->id) {
            case NCKEY_LEFT:
            case 'l': {
                focus_next();
                return true;
            }
            case NCKEY_RIGHT:
            case 'h': {
                focus_prev();
                return true;
            }
        }

        return false;
    }

    virtual void reformat() = 0;

    Context* get_focused_context() { return focused_context; }

protected:
    std::vector<Context*> contexts;

private:
    ncfw::RingIndex curr_context_idx;
    Context* focused_context = nullptr;
};

class VerticalLayout : public Layout {
    using Layout::Layout;
public:

    virtual int get_content_height() const override {
        int height = 0;
        for (auto c : contexts) {
            height += c->get_content_height();
        }
        return height;
    }
    virtual int get_content_width() const override {
        int max = 0;
        for (auto c : contexts) {
            max = std::max(max, c->get_content_width());
        }
        return max;
    }

    virtual void reformat() override {
        int y,x;
        get_yx(&y, &x);

        unsigned center_y, center_x;
        get_center_yx(&center_y, &center_x);

        if (alignment & ncfw::Align::Left) {
            x = 0;
        }
        if (alignment & ncfw::Align::Right) {
            x = get_dim_x()-get_content_width();
        }
        if (alignment & ncfw::Align::Top) {
            y = 0;
        }
        if (alignment & ncfw::Align::VCenter) {
            y = center_y-get_content_height()/2;
        }
        if (alignment & ncfw::Align::HCenter) {
            x = center_x-get_content_width()/2;
        }
        if (alignment & ncfw::Align::Bottom) {
            y = get_dim_y()-get_content_height();;
        }

        for (auto c : contexts) {
            // int xoffset = 0, yoffset = 0;
            // if (c->get_alignment() & ncfw::Align::Left) {
            //     xoffset = 0;
            // }
            // if (c->get_alignment() & ncfw::Align::Right) {
            //     // xoffset = get_content_width()-c->get_content_width();
            //     xoffset = get_content_width()-c->get_content_width();
            // }
            // // if (c->get_alignment() & ncfw::Align::Top) {
            // //     // y = 0;
            // // }
            // // if (c->get_alignment() & ncfw::Align::VCenter) {
            // //     // yoffset = center_y-get_content_height()/2;
            // // }
            // if (c->get_alignment() & ncfw::Align::HCenter) {
            //     xoffset = c->get_content_width()/2;
            // }
            // if (c->get_alignment() & ncfw::Align::Bottom) {
            //     // y = get_dim_y()-get_content_height();;
            // }

            c->move(y, x);
            y += c->get_content_height();
        }
    }
};

class HorizontalLayout : public Layout {
public:
    using Layout::Layout;

    virtual int get_content_width() const override {
        int width = 0;
        for (auto c : contexts) {
            width += c->get_content_width();
        }
        return width;

    }
    virtual int get_content_height() const override {
        int max = 0;
        for (auto c : contexts) {
            max = std::max(max, c->get_content_height());
        }
        return max;
    }


    void reformat() override {
        int y,x;
        get_yx(&y, &x);

        unsigned center_y, center_x;
        get_center_yx(&center_y, &center_x);

        if (alignment & ncfw::Align::Left) {
            x = 0;
        }
        if (alignment & ncfw::Align::Right) {
            x = get_dim_x()-get_content_width();
        }
        if (alignment & ncfw::Align::Top) {
            y = 0;
        }
        if (alignment & ncfw::Align::VCenter) {
            y = center_y-get_content_height()/2;
        }
        if (alignment & ncfw::Align::HCenter) {
            x = center_x-get_content_width()/2;
        }
        if (alignment & ncfw::Align::Bottom) {
            y = get_dim_y()-get_content_height();;
        }

        for (auto c : contexts) {
            int xoffset = 0, yoffset = 0;
            // if (c->get_alignment() & ncfw::Align::Left) {
            //     xoffset = 0;
            // }
            // if (c->get_alignment() & ncfw::Align::Right) {
            //     // xoffset = get_content_width()-c->get_content_width();
            //     xoffset = get_content_width()-c->get_content_width();
            // }
            // // if (c->get_alignment() & ncfw::Align::Top) {
            // //     // y = 0;
            // // }
            // // if (c->get_alignment() & ncfw::Align::VCenter) {
            // //     // yoffset = center_y-get_content_height()/2;
            // // }
            // if (c->get_alignment() & ncfw::Align::HCenter) {
            //     xoffset = c->get_content_width()/2;
            // }
            // if (c->get_alignment() & ncfw::Align::Bottom) {
            //     // y = get_dim_y()-get_content_height();;
            // }
            c->move(y+yoffset, x);
            x += c->get_content_width();
        }
    }
};

inline void center_context(Context* pile_root, Context* to_center) {
    auto pile = dynamic_cast<ncfw::Context*>(to_center->bottom_with(*to_center));
    auto testl = new ncfw::VerticalLayout(pile_root);
    testl->resize(pile_root->get_content_height(), pile_root->get_content_width());
    // testl->set_alignment(ncfw::Align::Center);
    // auto test = new ncfw::Text("BOOOOOIIII",  testl);
    // to_center->set_alignment(ncfw::Align::Center);
    testl->add(to_center);
}

}

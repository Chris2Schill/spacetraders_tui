#pragma once

#include "notcute/include/notcute/widget.hpp"
#include <notcute/float_widget.hpp>
#include <notcute/event_loop.hpp>

class HelpMenu : public notcute::FloatWidget {
public:
    struct HelpMenuOption {
        std::string keybinding;
        std::string description;
    };

    HelpMenu(const std::vector<HelpMenuOption>& options, notcute::Widget* parent = nullptr) 
        : FloatWidget(parent)
        , options(options){

        set_layout(new notcute::VBoxLayout(options.size()+2,50));
        move_to_term_center();
        set_focus_policy(notcute::FocusPolicy::FOCUS);

        set_attribute(ATTR_FOCUS_ON_SHOW, true);
    }

    bool on_keyboard_event(notcute::KeyboardEvent* e) override {
        switch(e->get_key()) {
            case NCKEY_ESC:
                done_showing();
                return true;
            default:
                return false;
        }
    }

    void draw(ncpp::Plane* p) override {
        notcute::fill(p, " ");
        // p->perimeter_rounded(0,0,0);

        // ncpp::Cell c(' ');
        // c.set_fg_rgb8(0, 000, 100);
        const auto GREEN = NCCHANNEL_INITIALIZER(0, 100, 0) << 32;
        //
        // c.set_fg_rgb8(0, 000, 100);
        const auto TEAL = NCCHANNEL_INITIALIZER(0, 100, 100) << 32;
        //
        // c.set_fg_rgb8(255, 255, 255);
        const auto WHITE = NCCHANNEL_INITIALIZER(255,255,255) << 32;
        //
        // p->set_fg_palindex(2);
        p->perimeter_double(0,GREEN,0);

        int left_col_width = 0;
        for (auto& opt : options) {
            if (opt.keybinding.size() > left_col_width) {
                left_col_width = opt.keybinding.size();
            }
        }
        left_col_width += 2; // left/right margins

        int desc_x = left_col_width + 1;

        for (int y = 0; y < options.size(); ++y) {
            HelpMenuOption& opt = options[y];

            // p->set_fg_palindex(7);
            p->set_channels(TEAL);
            p->putstr(y+1, desc_x-opt.keybinding.size()-1, opt.keybinding.c_str());

            // p->set_fg_palindex(255);
            p->set_channels(WHITE);
            p->putstr(y+1, desc_x, opt.description.c_str());
        }

        p->set_channels(GREEN);
        p->putstr(0,2, "Keybindings");

    }

private:
    std::vector<HelpMenuOption> options;
};

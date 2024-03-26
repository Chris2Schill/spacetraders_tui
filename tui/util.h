#pragma once

#include "notcute/box_layout.hpp"
#include <notcute/widget.hpp>
#include <notcute/frame_widget.hpp>
#include <notcute/list_widget.hpp>
#include <notcute/colors.hpp>

namespace sptr {

inline void set_focusable_color(notcute::Widget* focusable, bool focused) {
    // Colors
    notcute::Color frame_fg_focused               = notcute::DARK_YELLOW;//{000, 100, 000, NCALPHA_OPAQUE};
    notcute::Color frame_title_fg_focused         = {200, 200, 200, NCALPHA_OPAQUE};
    notcute::Color frame_fg_notfocused            = {235, 235, 235, NCALPHA_OPAQUE};
    notcute::Color frame_title_fg_notfocused      = {255, 255, 255, NCALPHA_OPAQUE};

    notcute::Color list_fg_selected_focused       = {000, 000, 000, NCALPHA_OPAQUE};
    notcute::Color list_fg_selected_notfocused    = {000, 100, 000, NCALPHA_OPAQUE};
    notcute::Color list_fg_notselected_focused    = {255, 000, 000, NCALPHA_OPAQUE};
    notcute::Color list_fg_notselected_notfocused = {255, 000, 000, NCALPHA_OPAQUE};
    notcute::Color list_bg_selected_focused       = {200, 200, 255, NCALPHA_OPAQUE};
    notcute::Color list_bg_selected_notfocused    = {000, 000, 000, NCALPHA_TRANSPARENT};
    notcute::Color list_bg_notselected_focused    = {000, 000, 000, NCALPHA_TRANSPARENT};
    notcute::Color list_bg_notselected_notfocused = {000, 000, 000, NCALPHA_TRANSPARENT};

    if (auto frame = dynamic_cast<notcute::FrameWidget*>(focusable); frame){
        auto frame_fg       = focused ? frame_fg_focused : frame_fg_notfocused;
        auto frame_title_fg = focused ? frame_title_fg_focused : frame_title_fg_notfocused;
        frame->set_frame_fg(frame_fg);
        frame->set_frame_title_fg(frame_title_fg);
    }


    if (auto lw = dynamic_cast<notcute::ListWidget*>(focusable); lw) {
        auto list_fg_sel    = focused ? list_fg_selected_focused : list_fg_selected_notfocused;
        auto list_fg_notsel = focused ? list_fg_notselected_focused : list_fg_notselected_notfocused;
        auto list_bg_sel    = focused ? list_bg_selected_focused : list_bg_selected_notfocused;
        auto list_bg_notsel = focused ? list_bg_notselected_focused : list_bg_notselected_notfocused;
        lw->set_fg_selected(list_fg_sel);
        lw->set_bg_selected(list_bg_sel);
        lw->set_fg_notselected(list_fg_notsel);
        lw->set_bg_notselected(list_bg_notsel);
    }

    focusable->redraw();
}

inline notcute::Widget* new_hbox(notcute::Widget* parent = nullptr) {
    auto wid = new notcute::Widget(parent);
    wid->set_layout(new notcute::HBoxLayout);
    return wid;
}

inline notcute::Widget* new_vbox(notcute::Widget* parent = nullptr) {
    auto wid = new notcute::Widget(parent);
    wid->set_layout(new notcute::VBoxLayout);
    return wid;
}

inline bool handle_leftright(notcute::Widget* wid, notcute::KeyboardEvent*e) {
    assert(wid->get_parent());
    switch(e->get_key()) {
        case 'l':
        case NCKEY_RIGHT:
            wid->get_parent()->get_parent()->get_parent()->focus_next_in_chain();
            return true;
        case 'h':
        case NCKEY_LEFT:
            wid->get_parent()->get_parent()->get_parent()->focus_prev_in_chain();
            return true;
        default:
            break;
    }
    return false;
}


} // end namespace sptr

#define SPTR_FOCUS_HANDLER_IMPL                                \
    bool on_focus_in_event(notcute::FocusEvent* e) override {  \
        sptr::set_focusable_color(this, true);                 \
        return true;                                           \
    }                                                          \
    bool on_focus_out_event(notcute::FocusEvent* e) override { \
        sptr::set_focusable_color(this, false);                \
        return true;                                           \
    }

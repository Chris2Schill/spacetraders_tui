#pragma once

#include <ncpp/NotCurses.hh>

#include <ncfw/context.hpp>
#include <ncfw/logger.h>

namespace ncfw {

// inline int resize_cb(ncplane* np) {
//     // log_debug("resizecb");
//     // ncplane_resize_realign(np);
//     auto* plane = ncpp::Plane::map_plane(np);
//
//
//     return 0;
// }


class FramedContext : public ncfw::Context {
public:
    FramedContext(ncfw::Context* parent, ncplane_options* opts = Context::default_options())
        : ncfw::Context(parent, opts)
    {
        frame = new Context(parent, opts);
        update_frame();
    }

    bool resize(int ylen, int xlen) const NOEXCEPT_MAYBE override {
        frame->resize(ylen, xlen);
        ylen = std::max(ylen-2, 0);
        xlen = std::max(xlen-2, 0);
        return Context::resize(ylen, xlen);
    }

    bool move(int y, int x) const NOEXCEPT_MAYBE override {
        frame->move(y,x);
        return Context::move(y+1,x+1);
    }

    int get_content_width() const override {
        return frame->get_content_width();
    }

    int get_content_height() const override {
        return frame->get_content_height();
    }

    Plane* reparent(const ncpp::Plane* p) const noexcept override {
        frame->reparent(p);
        return ncfw::Context::reparent(frame);
    }

    void update_frame() {
        uint64_t chans =  0;
        if (get_focused()) { chans = NCCHANNELS_INITIALIZER(0x20, 0xe0, 0x40, 0x20, 0x20, 0x20); }
        frame->perimeter_double(0, chans, 0);

        if (get_focused()) {
            frame->set_fg_palindex(1);
        }
        else {
            frame->set_fg_palindex(255);
        }
        frame->putstr(0, 2, title.c_str());
    }

    void set_title(const std::string& title) {
        this->title = title;
        update_frame();
    }

private:
    std::string title;
    Context* frame;
    
};

}



// class FramedScrollTextPlane : public FramedPlane {
// public:
//     FramedScrollTextPlane(int rows, int cols, int y, int x)
//         : FramedPlane(rows, cols, y, x)
//         , currentIndex(0, rows)
//     {
//     }
//
//     void update() override {
//         update_frame();
//
//         contents->erase();
//         for (unsigned i = currentIndex.get_value(), row = 0; i < lines.size(); ++i, row++) {
//             contents->printf(row, 0, lines[i].c_str());
//         }
//     }
//
//     void erase() {
//         lines.clear();
//     }
//     
//     void setLines(const std::vector<std::string>& lines) {
//         this->lines = lines;
//     }
//
//     void putstr(std::string str) {
//         lines.push_back(str);
//     }
//
//     bool offer_input(ncinput* ni) override {
//         switch(ni->id) {
//             case 'j': {
//                 currentIndex.next();
//                 log_debug(fmt::format("current idx = {}", currentIndex.get_value()));
//                 return true;
//                 break;
//             }
//             case 'k': {
//                 currentIndex.prev();
//                 log_debug(fmt::format("current idx = {}", currentIndex.get_value()));
//                 return true;
//                 break;
//             }
//         }
//         return false;
//     }
//
// protected:
//
//     RingIndex currentIndex;
//     std::vector<std::string> lines;
//     
// };

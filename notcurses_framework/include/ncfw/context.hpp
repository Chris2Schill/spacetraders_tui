#pragma once

#include <mutex>

#include <boost/signals2.hpp>

#include <ncpp/Pile.hh>
#include <ncpp/Plane.hh>

namespace ncfw {

enum eContext {
    CONTEXT_MAIN_MENU, 
    CONTEXT_DASHBOARD, 
};

struct ChangeContext {
    eContext contextId;
};

namespace Align {
    enum Align {
        Left   = 1,
        Right  = 1 << 1,
        Top    = 1 << 2,
        Bottom = 1 << 3,
        VCenter = 1 << 4,
        HCenter = 1 << 5,
        Center = VCenter | HCenter,
    };
}

struct Context : public ncpp::Plane {

    virtual ~Context() = default;

    enum eFocus {
        FOCUSED,
        NOT_FOCUSED
    };

    static ncplane_options* default_pile_options() {
        auto& nc = ncpp::NotCurses::get_instance();
        unsigned rows, cols;
        nc.get_term_dim(&rows, &cols);

        static ncplane_options opts = {
            // .rows = rows,
            // .cols = cols,
            .flags = NCPLANE_OPTION_MARGINALIZED
        };

        return &opts;
    }

    static ncplane_options* default_options() {
        auto& nc = ncpp::NotCurses::get_instance();
        unsigned rows, cols;
        nc.get_term_dim(&rows, &cols);

        static ncplane_options opts = {
            .y = 0,
            .x = 0,
            .rows = rows,
            .cols = cols,
        };

        return &opts;
    }

    Context(Context* parent, ncplane_options* opts = default_options())
        : ncpp::Plane(parent, *opts) { 
        reparent(parent);
    }

    Context(Context* parent, ncplane_options opts) : Context(parent, &opts) { }

    Context (ncplane_options const* nopts = default_pile_options(), ncpp::NotCurses* ncinst = nullptr)
        : ncpp::Plane (ncinst)
    {
        if (nopts == nullptr) {
            throw std::invalid_argument ("'nopts' must be a valid pointer");
        }

        notcurses *n;
        if (ncinst == nullptr) {
            n = ncpp::NotCurses::get_instance ();
        } else {
            n = *ncinst;
        }

        ncplane *pile = ncpile_create (n, nopts);
        if (pile == nullptr) {
            throw ncpp::init_error ("Notcurses failed to create a new pile");
        }

        set_plane (pile);
    }

    // std::vector<Panel*> panels;
    // int curr_panel_idx = 0;
    // Panel* focused_panel = nullptr;

    virtual void update() { }
    virtual void refresh() {}
    virtual bool offer_input(ncinput* ni) { return false; }

    void set_focused(bool focused)
    {
        bool f = is_focused;

        if (is_focusable) {
            f = focused;
        }
        else {
            f = false;
        }

        if (f != is_focused) {
            is_focused = f;
            focused_state_changed(is_focused);
        }
    }
    bool get_focused() const { return is_focused; }

    void set_focusable(bool focusable) { is_focusable = focusable; }
    bool get_focusable() const { return is_focusable; }

    bool render () const NOEXCEPT_MAYBE
    {
        return error_guard (ncpile_render (to_ncplane ()), -1);
    }

    bool rasterize () const NOEXCEPT_MAYBE
    {
        return error_guard (ncpile_rasterize (to_ncplane ()), -1);
    }

    virtual int get_content_height() const {
        return get_dim_y();

    }

    virtual int get_content_width() const {
        return get_dim_x();
    }

    void get_center_yx(unsigned* y, unsigned* x) {
        int curry,currx;
        get_yx(&curry,&currx);
        if (y) {
            *y = ((2*curry)+get_dim_y())/2;
        }

        if (x) {
            *x = ((2*currx)+get_dim_x())/2;
        }
    }

    bool show () const NOEXCEPT_MAYBE
    {
        if (!render ()) {
            return false;
        }

        return rasterize ();
    }

    static Plane* top_with (const Plane& plane) noexcept
    {
        ncplane* ret = ncpile_top (const_cast<Plane&>(plane));
        if (ret == nullptr) {
            return nullptr;
        }

        return map_plane (ret);
    }

    static Plane* bottom_with (const Plane& plane) noexcept
    {
        ncplane* ret = ncpile_bottom (const_cast<Plane&>(plane));
        if (ret == nullptr) {
            return nullptr;
        }

        return map_plane (ret);
    }

    std::string debug_name;

    void set_alignment(int align) {
        alignment = align;
    }
    int get_alignment() const { return alignment; }

    int alignment = ncfw::Align::Center;

    // ncfw::Context* get_subcontext() const { return subcontext; }
    // void set_subcontext(ncfw::Context* ctx) { subcontext = ctx; }

    boost::signals2::signal<void(bool)> focused_state_changed;

    // ncfw::Context* subcontext = nullptr;
protected:
    std::mutex mtx;
private:
    bool is_focused = false;
    bool is_focusable = false;
};

class Text : public Context {
public:
    Text(const std::string& text, Context* parent)
        : Context(parent, Context::default_options())
        , text(text)
    {
        resize(1, std::max(1, (int)text.size()));
        set_fg_palindex(3);
        putstr(text.c_str());
    }

    void set_text(const std::string& t) {
        text = t;
        erase();
        resize(1, text.size());
        set_fg_palindex(3);
        putstr(text.c_str());
    }


private:
    std::string text;
};

class List : public Context {
};

}

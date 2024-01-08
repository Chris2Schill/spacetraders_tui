#pragma once

#include <memory>
#include <boost/signals2.hpp>
#include <ncpp/Selector.hh>
#include <functional>

#include "context.hpp"

namespace ncfw {

using PlanePtr = std::shared_ptr<ncpp::Plane>;
using SelectorPtr = std::shared_ptr<ncpp::Selector>;

// template<typename T>
// const char* to_ncselector_option(const T& item) {
//     return item.c_str();
// }

class SelectorItem {
public:

    SelectorItem(const std::string& name, void* item = nullptr)
        : name(name)
        , item(item)
    {
        ncitem = new ncselector_item{};
        ncitem->option = name.c_str();
        ncitem->desc = "";
    }

    ~SelectorItem() { }

    ncselector_item* to_ncselector_item() const {
        return ncitem;
    }

    std::string& get_name() { return name; }

    template<typename T>
    T* get_item() { return static_cast<T*>(item); }

private:
    std::string      name;
    ncselector_item* ncitem;
    void*            item;
};

class Selector : public Context {
public:
    Selector(Context* parent, ncplane_options* opts = Context::default_options(), ncselector_options* sopts = nullptr)
        : Context(parent, opts)
    {
        set_focusable(true);

        // TODO: Why do i have to set selectors to Left in order to center them??
        set_alignment(ncfw::Align::Left);

        // Default options globally for Selectors
        auto& dsopts = ncpp::Selector::default_options;
        dsopts.opchannels = NCCHANNELS_INITIALIZER(0xe0, 0x80, 0x40, 0, 0, 0);
        // dsopts.descchannels = NCCHANNELS_INITIALIZER(0x80, 0xe0, 0x40, 0, 0, 0);
        // dsopts.footchannels = NCCHANNELS_INITIALIZER(0xe0, 0, 0x40, 0x20, 0, 0);
        // dsopts.titlechannels = NCCHANNELS_INITIALIZER(0xff, 0xff, 0x80, 0, 0, 0x20);
        // dsopts.boxchannels = NCCHANNELS_INITIALIZER(0x1, 0x1, 0x01, 1, 1, 0x01);
        // dsopts.boxchannels = NCCHANNELS_INITIALIZER(255, 0x0, 0x00, 255, 0, 0x00);
        // dsopts.boxchannels |= 0xFFFFFFFF & NC_BG_ALPHA_MASK;
        dsopts.maxdisplay = 7;

        if (!sopts) {
            sopts = &ncpp::Selector::default_options; 
        }

        // auto sopts = dsopts;
        selector = std::make_shared<ncpp::Selector>(new Context(this), sopts);

        selector->get_plane()->set_fg_palindex(255);
    }

    // void add_item(const char* option, std::function<void()> f) {
    void add_item(SelectorItem* item) {
        items.push_back(item);
        selector->additem(item->to_ncselector_item());
        selector->get_plane()->resize_realign();
    }

    SelectorItem* get_selected() {
        return items[selected_idx];
    }

    boost::signals2::signal<void(SelectorItem*)> item_selected;

    bool offer_input(ncinput* ni) override {
        switch (ni->id) {
            case 'j':
            case NCKEY_DOWN:
                if (selected_idx == items.size()-1) {
                    for (int i = 0; i < items.size()-1; ++i)  {
                        selector->previtem();
                    }
                    selected_idx = 0;
                }
                else {
                    selector->nextitem();
                    selected_idx++;
                }
                return true;

            case 'k':
            case NCKEY_UP:
                if (selected_idx == 0) {
                    for (int i = 0; i < items.size()-1; ++i)  {
                        selector->nextitem();
                    }
                    selected_idx = items.size()-1;
                }
                else {
                    selector->previtem();
                    selected_idx--;
                }
                return true;

            case NCKEY_ENTER:
                // funcMap[selector->get_selected()]();
                item_selected(items[selected_idx]);
                return true;
            default:
                return false;
        }
        return false;
    }
private:

    std::vector<SelectorItem*> items;
    // std::unordered_map<std::string, std::function<void()>> funcMap;

    int selected_idx = 0;
    SelectorPtr selector = nullptr;
};

}

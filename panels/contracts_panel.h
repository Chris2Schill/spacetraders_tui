#pragma once

#include <ncpp/Pile.hh>
#include <ncfw/context.hpp>
#include <CppRestOpenAPIClient/api/ContractsApi.h>

#include <ncfw/context.hpp>
#include <ncfw/selector.hpp>
#include <ncfw/framed_context.hpp>
#include "../sptr_api.h"

static ncselector_options sopts{
    .opchannels = NCCHANNELS_INITIALIZER(0xe0, 0x80, 0x40, 0, 0, 0),
    .descchannels = NCCHANNELS_INITIALIZER(0x80, 0xe0, 0x40, 0, 0, 0),
    .titlechannels = NCCHANNELS_INITIALIZER(0xff, 0xff, 0x80, 0, 0, 0x20),
    .footchannels = NCCHANNELS_INITIALIZER(0xe0, 0, 0x40, 0x20, 0, 0),
};



// template<typename T>
// class SelectorPanel :public FramedContext {
// public:
//     SelectorPanel(ncpp::Pile* pile)
//         : FramedContext(pile)
//         , selectionIdx(0,0)
//     {
//         itemContents = new ncpp::Plane(contents, 35, 50, 0, 40);
//         renew();
//         // ctx = new Context{};
//     }
//
//     void renew() {
//         delete itemList;
//         auto p = ncpp::Plane(contents, 30, 20, 0, 0);
//         itemList = new ncpp::Selector(p, &sopts);
//     }
//
//     bool offer_input(ncinput* ni) override {
//         if (in_context) {
//             bool handled = ctx->offer_input(ni);
//             if (handled) { return true; }
//         }
//
//         switch (ni->id) {
//             case 'j':
//             case NCKEY_DOWN:
//                 itemList->nextitem();
//                 selectionIdx.next();
//                 draw_item_contents();
//                 break;
//
//             case 'h':
//             case NCKEY_UP:
//                 itemList->previtem();
//                 selectionIdx.prev();
//                 draw_item_contents();
//                 break;
//
//             case NCKEY_ENTER:
//                 in_context = !in_context;
//                 break;
//             default:
//                 return false;
//         }
//         return true;
//     }
//
//     virtual void draw_item_contents() {}
//     virtual void item_selected(T*) = 0;
//
//     void additem(ncselector_item* item) {
//         itemList->additem(item);
//         selectionIdx.set_max(selectionIdx.get_max()+1);
//     }
//
//     T* get_selection() { return items[selectionIdx.get_value()].get(); }
//
// protected:
//     ncpp::Selector* itemList = nullptr;
//     ncpp::Plane*    itemContents = nullptr;
//     std::vector<std::shared_ptr<T>> items;
//     RingIndex selectionIdx;
//     bool dirty = false;
//     ncfw::Context* ctx;
//     bool in_context = false;
// };

struct ncselector_item_with_userptr : public ncselector_item {
    virtual ~ncselector_item_with_userptr() = default;
    void* userptr;
};

class Selectable : public ncfw::Context {
public:
    Selectable(ncfw::Context* parent, int y, int x, const std::string& text)
        : ncfw::Context(parent)
        ,text(text)
    {
        set_fg_palindex(1);
        putstr(text.c_str());
    }

    void refresh() override {}
    void update() override {}
    bool offer_input(ncinput* ni) override {
        if (ni->id == NCKEY_ENTER && select) {
            select();
            return true;
        }
        return false;
    }

    std::function<void()> select;

private:
    std::string text;
};

class ContractsPanel : public ncfw::FramedContext {
public:
    ContractsPanel(ncfw::Context* parent, ncplane_options* opts = ncfw::Context::default_options())
        : ncfw::FramedContext(parent, opts)
        , api(sptr::get_api_client())
    {
        renew();
        refresh();
    }

    void refresh() override {
        api.getContracts({},{})
           .then([this](auto task){
                   std::scoped_lock lock(mtx);
                   contracts = task.get()->getData();
                   for (auto c : contracts) {
                       log_debug(c->toJson().serialize());
                   }
                    dirty = true;
               });
    }

    void draw_subcontent(ncfw::FramedContext* subcontext) {
        subcontext->erase();
        subcontext->set_title("Contracts");
        // api::Contract* contract = get_selection();
        if (contracts.size() == 0) { return; }
        auto contract = contracts[0];

        subcontext->erase();
        // dynamic_cast<FramedContext*>(subcontext)->update_frame();
        if (contract) {
            std::string accepted = contract->isAccepted() ? "ACCEPTED" : "PENDING";
            subcontext->printf(0,0,  "ID: %s           %s", contract->getId().c_str(), accepted.c_str());
            subcontext->printf(1,0,  "Faction: %s", contract->getFactionSymbol().c_str());
            subcontext->printf(2,0,  "Type: %s", contract->getType().c_str());
            subcontext->printf(3,0,  "Terms:");
            subcontext->printf(4,0,  "    Deadline: %s", contract->getTerms()->getDeadline().to_string().c_str());
            subcontext->printf(5,0,  "    Payment:");
            subcontext->printf(6,0,  "        On Accepted:  $%d", contract->getTerms()->getPayment()->getOnAccepted());
            subcontext->printf(7,0,  "        On Fulfilled: $%d", contract->getTerms()->getPayment()->getOnFulfilled());
            subcontext->printf(9,0,  "    Deliver:");

            auto& goods = contract->getTerms()->getDeliver();
            // if (!destinationSelectable) {
            //     destinationSelectable = new Selectable(itemContents, 10, 22, goods[0]->getDestinationSymbol());
            // }
            subcontext->printf(9,0, "        %ld Payloads: %s %d/%d", goods.size(), goods[0]->getTradeSymbol().c_str(), goods[0]->getUnitsFulfilled(), goods[0]->getUnitsRequired());

            // itemContents->printf(10,0, "        Destination: %s", goods[0]->getDestinationSymbol().c_str());
            subcontext->printf(10,0, "        Destination: %s", goods[0]->getDestinationSymbol().c_str());
        }
    }

    boost::signals2::signal<void()> data_changed;

    void renew() {
        delete selector;
        ncplane_options popts = *ncfw::Context::default_options();
        popts.y = 0;
        popts.x = 0;
        popts.rows = 10;
        popts.cols = 50;
        // auto p = new ncfw::Context(this, ncplane_options{.rows = 10, .cols = 50});
        // auto ctx = new ncfw::Context();
        auto p = new ncfw::Context(this, &popts);
        // p->move(get_y(), get_x());
        selector = new ncfw::Selector(p, &popts);
        selector->resize(get_content_height(), get_content_width());
        // selector->move(get_y(), get_x());

        // ctx->show();
        // ncinput ni;
        // ncpp::NotCurses::get_instance().get(true, &ni);
    }

    // bool offer_input(ncinput* ni) override {
    //     bool handled = SelectorPanel<api::Contract>::offer_input(ni);
    //     if (handled) { return true; }
    //
    //     switch (ni->id) {
    //         case 'a':
    //             item_selected(get_selection()); 
    //             break;
    //     }
    //     return false;
    // }

    void update() override {
        erase();

        if (dirty) {
            renew();
            {
                std::scoped_lock lock(mtx);
                for (auto c : contracts) {
                    selector->add_item(new ncfw::SelectorItem(c->getId()));
                }
                dirty = false;
                data_changed();
            }
        }

        update_frame();
        set_title("Contracts");
    }

private:
    // ncpp::Selector* selector = nullptr;
    ncfw::Selector* selector = nullptr;
    bool dirty = true;
    api::ContractsApi api;
    std::vector<std::shared_ptr<api::Contract>> contracts;
};

// class ContractsPanel : public SelectorPanel<api::Contract> {
// public:
//     ContractsPanel(ncpp::Pile* pile) 
//         : SelectorPanel(pile)
//         , api(sptr::get_api_client())
//     {
//     }
//
//     void refresh() override {
//
//         api.getContracts({},{})
//            .then([this](auto task){
//                    std::scoped_lock lock(mtx);
//                    items = task.get()->getData();
//                     for (auto c : items) {
//                         log_debug(c->toJson().serialize());
//                     }
//                     dirty = true;
//                });
//     }
//
//     void item_selected(api::Contract* contract) override {
//         if (!contract->isAccepted()) {
//             api.acceptContract(contract->getId());
//         }
//     }
//
//     bool offer_input(ncinput* ni) override {
//         bool handled = SelectorPanel<api::Contract>::offer_input(ni);
//         if (handled) { return true; }
//
//         switch (ni->id) {
//             case 'a':
//                 item_selected(get_selection()); 
//                 break;
//         }
//         return false;
//     }
//
//     Selectable* destinationSelectable = nullptr;
//     virtual void draw_item_contents() override {
//         api::Contract* contract = get_selection();
//
//         itemContents->erase();
//         if (contract) {
//             std::string accepted = contract->isAccepted() ? "ACCEPTED" : "PENDING";
//             itemContents->printf(0,0,  "ID: %s           %s", contract->getId().c_str(), accepted.c_str());
//             itemContents->printf(1,0,  "Faction: %s", contract->getFactionSymbol().c_str());
//             itemContents->printf(2,0,  "Type: %s", contract->getType().c_str());
//             itemContents->printf(4,0,  "Terms:");
//             itemContents->printf(5,0,  "    Deadline: %s", contract->getTerms()->getDeadline().to_string().c_str());
//             itemContents->printf(6,0,  "    Payment:");
//             itemContents->printf(7,0,  "        On Accepted:  $%d", contract->getTerms()->getPayment()->getOnAccepted());
//             itemContents->printf(8,0,  "        On Fulfilled: $%d", contract->getTerms()->getPayment()->getOnFulfilled());
//             itemContents->printf(9,0,  "    Deliver:");
//
//             auto& goods = contract->getTerms()->getDeliver();
//             if (!destinationSelectable) {
//                 destinationSelectable = new Selectable(itemContents, 11, 22, goods[0]->getDestinationSymbol());
//             }
//             itemContents->printf(10,0, "        %ld Payloads: %s %d/%d", goods.size(), goods[0]->getTradeSymbol().c_str(), goods[0]->getUnitsFulfilled(), goods[0]->getUnitsRequired());
//
//             // itemContents->printf(11,0, "        Destination: %s", goods[0]->getDestinationSymbol().c_str());
//             itemContents->printf(11,0, "        Destination: ");
//         }
//     }
//
//     void update() override {
//         if (dirty) {
//             renew();
//             {
//                 std::scoped_lock lock(mtx);
//                 for (auto c : items) {
//                     ncselector_item* i = new ncselector_item;
//                     i->option = strdup(c->getId().c_str());
//                     // i->userptr = &c;
//                     additem(i);
//                     log_debug("added contract to selector");
//                 }
//                 dirty = false;
//                 draw_item_contents();
//             }
//         }
//
//         update_frame();
//         set_title("Contracts");
//     }
// private:
//     api::ContractsApi api;
// };

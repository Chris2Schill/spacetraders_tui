#pragma once

#include <vector>

#include <notcute/frame_widget.hpp>
#include <notcute/list_widget.hpp>
#include <CppRestOpenAPIClient/api/ContractsApi.h>

#include "CppRestOpenAPIClient/ApiException.h"
#include "notcute/widget.hpp"
#include <sptr/api.h>
#include "events.h"
#include "help_menu.hpp"
#include "util.h"

using ContractPtr = std::shared_ptr<api::Contract>;
using Contracts   = std::vector<ContractPtr>;


namespace notcute {
    template<>
    inline std::string to_string<ContractPtr>(const ContractPtr& c) {
        std::string accepted = c->isAccepted() ? "ACCEPTED" : "PENDING";
        return c->getId() + " - " + accepted;
    }
}


class ContractWidget : public notcute::FrameWidget {
public:
    ContractWidget(notcute::Widget* parent = nullptr)
        :notcute::FrameWidget(parent)
    {
        set_layout(new notcute::VBoxLayout);
    }

    void set_contract(ContractPtr c) {
        contract = c;
        redraw();
    }

    void draw(ncpp::Plane* p) {
        FrameWidget::draw(p);
        if (contract) {
            std::string accepted = contract->isAccepted() ? "ACCEPTED" : "PENDING";
            p->printf(1,1,  "ID: %s           %s", contract->getId().c_str(), accepted.c_str());
            p->printf(2,1,  "Faction: %s", contract->getFactionSymbol().c_str());
            p->printf(3,1,  "Type: %s", contract->getType().c_str());
            p->printf(4,1,  "Terms:");
            p->printf(5,1,  "    Deadline: %s", contract->getTerms()->getDeadline().to_string().c_str());
            p->printf(6,1,  "    Payment:");
            p->printf(7,1,  "        On Accepted:  $%d", contract->getTerms()->getPayment()->getOnAccepted());
            p->printf(8,1,  "        On Fulfilled: $%d", contract->getTerms()->getPayment()->getOnFulfilled());
            p->printf(9,1,  "    Deliver:");

            auto& goods = contract->getTerms()->getDeliver();
            // if (!destinationSelectable) {
            //     destinationSelectable = new Selectable(itemContents, 10, 22, goods[0]->getDestinationSymbol());
            // }
            p->printf(9,0, "        %ld Payloads: %s %d/%d", goods.size(), goods[0]->getTradeSymbol().c_str(), goods[0]->getUnitsFulfilled(), goods[0]->getUnitsRequired());

            // itemContents->printf(10,0, "        Destination: %s", goods[0]->getDestinationSymbol().c_str());
            p->printf(10,0, "        Destination: %s", goods[0]->getDestinationSymbol().c_str());
        }
    }

    ContractPtr contract = nullptr;
};

// class ContractsContentPane : public notcute::FrameWidget {
// public:
//     ContractsContentPane(notcute::Widget* parent = nullptr)
//         :notcute::FrameWidget(parent)
//     {
//         set_layout(new notcute::VBoxLayout);
//         // get_layout()->add_widget(new notcute::TextWidget("CONTRACTS BABY", this));
//         get_layout()->set_size(100,100);
//         // get_layout()->set_margins_ltrb(1,1,1,1);
//         // get_layout()->set_behave(LAY_FILL);
//         cw = new ContractWidget(this);
//
//         get_layout()->add_widget(cw);
//
//         set_title("Contracts");
//     }
//
//     void set_contract(ContractPtr c) {
//         cw->set_contract(c);
//     }
//
//     ContractWidget* cw = nullptr;
// };

class ContractsListWidget : public notcute::ListWidget {
public:

    using ContractListItem = notcute::ListItem_t<ContractPtr>;

    ContractsListWidget(Widget* parent = nullptr)
        : ListWidget(parent)
        , api(sptr::get_api_client())
    {
        request_data();
        get_layout()->set_size(6, 0);
        get_layout()->set_behave(LAY_HFILL);
        set_title("Contracts");
        set_name("Contracts");
        set_focus_policy(notcute::FocusPolicy::FOCUS);

        content_pane = new ContractWidget(this);

        item_hovered.connect([this](notcute::ListItem* item){
                ContractPtr contract = notcute::list_widget_item_t_get_item<ContractPtr>(item);
                notcute::log_debug("selected contract! {}", contract->getId());
                content_pane->set_contract(contract);
            });
    }

    bool on_event(notcute::Event* e) override {
        switch(static_cast<sptr::EventType>(e->get_type())) {
            case sptr::PAYLOAD_EVENT: {
                auto payload_event = static_cast<PayloadEvent<Contracts>*>(e);
                contracts = payload_event->get_payload();
                clear();
                for (ContractPtr c : contracts) {
                    notcute::log_debug("{}", c->toJson().serialize());
                    auto item = new ContractListItem(c);
                    add_item(item);
                }
                return true;
            }
            case sptr::CONTRACT_ACCEPTED_EVENT: {
                auto payload_event = static_cast<PayloadEvent<ContractPtr>*>(e);
                auto contract = payload_event->get_payload();
                for (auto& ct : contracts) {
                    if (ct->getId() == contract->getId()) {
                        ct = contract;
                        break;
                    }
                }
                redraw();
                content_pane->redraw();
                return true;
            }
            default:
                return ListWidget::on_event(e);
        }


        return Widget::on_event(e);
    }

    notcute::FrameWidget* get_content_pane() { return content_pane; }

    bool on_keyboard_event(notcute::KeyboardEvent* e) override {
        if (sptr::handle_leftright(this, e)) {
            return true;
        }

        switch(e->get_key()) {
            case 'a':
                accept_contract(get_selected_contract());
                return true;
            case '?':
                show_help_menu();
                return true;
            default:
                return ListWidget::on_keyboard_event(e);
        }
    }

    void request_data() {
        api.getContracts({},{})
           .then([this](auto task){
                   API_ERROR_GUARD_START
                   auto new_contracts = task.get()->getData();
                   auto event = new PayloadEvent(this, sptr::PAYLOAD_EVENT, new_contracts);
                   notcute::EventLoop::get_instance()->post(event);
                   API_ERROR_GUARD_END
               });
    }

    ContractPtr get_selected_contract() {
        return contracts[get_selected_idx()];
    }

    void accept_contract(ContractPtr c) {
        api.acceptContract(c->getId()).then([this](auto task) {
                ContractPtr contract = task.get()->getData()->getContract();
                auto event = new PayloadEvent(this, sptr::CONTRACT_ACCEPTED_EVENT, contract);
                notcute::EventLoop::get_instance()->post(event);
            });
    }

    void show_help_menu() {

        auto fw = new HelpMenu({ {"a", "Accept Contract"}, },
                               get_top_level_widget());
        fw->show();
        delete fw;
        redraw();
    }

    SPTR_FOCUS_HANDLER_IMPL

private:
    api::ContractsApi api;
    Contracts contracts;
    ContractWidget* content_pane = nullptr;
};

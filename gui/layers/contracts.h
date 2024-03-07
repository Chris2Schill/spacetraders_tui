#pragma once

#include "layer.h"
#include "sptr/data.h"
#include <sptr/sptr.h>

#include <imgui.h>

struct ContractsLayer : public Layer {
  void render() {
    auto &gs = sptr::GameState::instance();
    ImGui::Begin("Contracts");

    if (gs.pending_contracts.size() > 0) {
      std::stringstream ss;
      ss << "Pending (" << gs.pending_contracts.size() << ")";
      std::string pending = ss.str();
      if (ImGui::TreeNode(pending.c_str())) {
        for (auto &contract : gs.pending_contracts) {
          render_contract(contract);
        }
        ImGui::TreePop();
      }
    }

    if (gs.active_contracts.size() > 0) {
      std::stringstream ss;
      ss << "Accepted (" << gs.active_contracts.size() << ")";
      std::string accepted = ss.str();
      if (ImGui::TreeNode(accepted.c_str())) {
        for (auto &contract : gs.active_contracts) {
          render_contract(contract);
        }
        ImGui::TreePop();
      }
    }
    ImGui::End();
  }

  void render_contract(const sptr::Contract contract) {
    if (ImGui::TreeNode(contract->getId().c_str())) {
      ImGui::LabelText("Faction", "%s", contract->getFactionSymbol().c_str());
      ImGui::LabelText("Type", "%s", contract->getType().c_str());
      if (ImGui::TreeNode("Terms")) {
        ImGui::LabelText(
            "Deadline", "%s",
            contract->getTerms()->getDeadline().to_string().c_str());
        if (ImGui::TreeNode("Payment")) {
          ImGui::LabelText("On Accepted", "$%d",
                           contract->getTerms()->getPayment()->getOnAccepted());
          ImGui::LabelText(
              "On Fulfilled", "$%d",
              contract->getTerms()->getPayment()->getOnFulfilled());
          ImGui::TreePop();
        }
        auto &goods = contract->getTerms()->getDeliver();
        if (ImGui::TreeNode("Deliver")) {
          ImGui::LabelText("", "%ld Payloads: %s %d/%d", goods.size(),
                           goods[0]->getTradeSymbol().c_str(),
                           goods[0]->getUnitsFulfilled(),
                           goods[0]->getUnitsRequired());
          ImGui::LabelText("Destination", "%s",
                           goods[0]->getDestinationSymbol().c_str());
          ImGui::TreePop();
        }

        if (!contract->isAccepted()) {
            if (ImGui::Button("Accept")) {
                sptr::DataProvider::instance().request_accept_contracts(contract);
            }
        }

        ImGui::TreePop();
      }
      ImGui::TreePop();
    }
  }
};

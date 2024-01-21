#pragma once


#include <vector>
#include <functional>
#include <stack>
#include <notcute/widget.hpp>
#include "util.h"

// Describes a focus tree that can be used to link widget's focus
struct FocusNode {
    notcute::Widget*      widget;  // a widget that can receive "focus"
    void*                 userptr; // anything extra you want
    std::function<void()> on_focus_callback;
    std::function<void()> off_focus_callback;

    FocusNode* next;     // the next node
    FocusNode* prev;     // the prev node
    FocusNode* selected; // can be used to point to any other node, can even be a different focus graph
};

// a helper container to make construction of graph easier
struct FocusNodeEntry {
    notcute::Widget* widget; 
    void*            userptr; 
};

inline std::vector<FocusNode*> setup_focus_graph(const std::vector<FocusNodeEntry>& focusables) {
    // Create focus nodes for each focusable
    std::vector<FocusNode*> nodes;
    for (auto focusable : focusables) {
        FocusNode* node = new FocusNode;
        node->widget = focusable.widget;
        node->userptr = focusable.userptr;
        node->off_focus_callback = [=](){ sptr::set_focusable_color(node->widget, false); };
        node->on_focus_callback =  [=](){ sptr::set_focusable_color(node->widget, true);  };
        nodes.push_back(node);

        // set their colors at the start
        sptr::set_focusable_color(node->widget, true);
        sptr::set_focusable_color(node->widget, false);
    }

    // link prev/next nodes 
    FocusNode* first = nodes.front();
    first->prev = nodes.back();
    first->next = *(++nodes.begin());
    FocusNode* last = nodes.back();
    last->next = nodes.front();
    last->prev = *(--(--nodes.end()));
    for (int i = 1; i < nodes.size()-1; ++i) {
        FocusNode* node = nodes[i];
        node->next = nodes[i+1];
        node->prev = nodes[i-1];
    }

    return nodes;
}

struct FocusStackEntry {
    // the widget that orchestrates the focus graph. This is the widget
    // that actuall has focus, it will delegate input events to
    // nodes in the tree as it sees fit
    notcute::Widget* orchestrator;

    // pointer to the focus node that had "focus" at this snapshot in time
    FocusNode**      active_node;
};

inline std::stack<FocusStackEntry>& focus_stack() {
    static std::stack<FocusStackEntry> nodes;
    return nodes;
}

inline void focus_stack_push(FocusStackEntry n) {
    assert(n.orchestrator->get_focus_policy() == notcute::FocusPolicy::FOCUS);

    if (focus_stack().size() > 0) {
        FocusStackEntry top = focus_stack().top();
        FocusNode* node = *top.active_node;
        if (node->off_focus_callback) { node->off_focus_callback(); }
    }

    focus_stack().push(n);
    n.orchestrator->set_focus();
    FocusNode* node = *n.active_node;
    if (node->on_focus_callback) { node->on_focus_callback(); }
}

inline FocusStackEntry focus_stack_pop() {
    auto& fs = focus_stack();
    assert(fs.size() > 0);
    FocusStackEntry popped = fs.top();
    fs.pop();
    FocusStackEntry top = fs.top();
    assert(top.orchestrator->get_focus_policy() == notcute::FocusPolicy::FOCUS);
    top.orchestrator->set_focus();

    FocusNode* popped_node = *popped.active_node;
    FocusNode* top_node    = *top.active_node;

    if (popped_node->off_focus_callback) { popped_node->off_focus_callback(); }
    if (top_node->on_focus_callback) { top_node->on_focus_callback(); }

    return popped;
}

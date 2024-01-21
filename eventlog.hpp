#pragma once


#include <notcute/list_widget.hpp>
#include "events.h"

class EventLogEvent : public notcute::Event {
public:
    EventLogEvent(notcute::Widget* sender,
                  int type)
        : notcute::Event(sender,static_cast<notcute::Event::EventType>(type))
    {}
private:

};

class EventLogWidget : public notcute::ListWidget {
public:
    struct Event {
        std::function<void()> action;
    };
    using EventPtr = std::shared_ptr<Event>;

    EventLogWidget(Widget* parent = nullptr)
        :notcute::ListWidget(parent)
    {
        set_layout(new notcute::HBoxLayout);
        get_layout()->set_size(6, 0);
        get_layout()->set_behave(LAY_HFILL);
        set_focus_policy(notcute::FocusPolicy::FOCUS);
        set_title("Event Log");
        set_name("Event Log");
    }

    bool on_event(notcute::Event* e) override {
        switch(static_cast<sptr::EventType>(e->get_type())) {
            case sptr::EVENTLOG_EVENT: {
                EventLogEvent* event = static_cast<EventLogEvent*>(e);
                // EventPtr ep = event->get_event();
                return true;
            }
            default:
                break;
        }
        return false;
    }

    notcute::signal<void()> on_next_pane;
    notcute::signal<void()> on_prev_pane;

    std::queue<EventPtr> events;
};

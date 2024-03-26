#pragma once


#include <notcute/list_widget.hpp>
#include "events.h"
#include "util.h"

class EventLogEvent : public notcute::Event {
public:
    EventLogEvent(notcute::Widget* sender,
                  int type)
        : notcute::Event(static_cast<notcute::Event::EventType>(type), sender)
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
        return ListWidget::on_event(e);
    }

    bool on_keyboard_event(notcute::KeyboardEvent* e) override {
        if (sptr::handle_leftright(this, e)) {
            return true;
        }
        return ListWidget::on_keyboard_event(e);
    }

    SPTR_FOCUS_HANDLER_IMPL
private:

    std::queue<EventPtr> events;
};

#pragma once

#include <notcute/event_loop.hpp>

namespace sptr {

    enum EventType {
        PAYLOAD_EVENT = notcute::Event::USER_EVENT,
        CONTRACT_ACCEPTED_EVENT,
        EVENTLOG_EVENT,
    };
}


// Generic event that carries any payload
template<typename T>
class PayloadEvent : public notcute::Event {
public:
    PayloadEvent(notcute::Widget* sender,
                 int type,
                 const T& p)
        : notcute::Event(static_cast<notcute::Event::EventType>(type), sender, sender)
        , payload(p)
    {}

    const T& get_payload() const { return payload; }


private:
    notcute::Event::EventType type;
    T payload;
};

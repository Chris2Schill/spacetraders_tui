#pragma once

#include "event_bus.h"
#include "api.h"
#include "data.h"
#include "events.h"


namespace sptr {

    inline event_bus::Dispatcher* get_event_bus() {
        return &event_bus::Dispatcher::getInstance();
    }
}

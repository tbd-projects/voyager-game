//
// Created by volodya on 09.05.2021.
//

#ifndef VOYAGER_CLOSE_EVENT_H
#define VOYAGER_CLOSE_EVENT_H

#include "event_controller/event.h"

namespace event_controller {
    class CloseEvent: public Event {
    public:
        CloseEvent(): Event(EventType::close) {};
    };

}
#endif //VOYAGER_CLOSE_EVENT_H

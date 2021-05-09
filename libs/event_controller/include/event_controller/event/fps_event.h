//
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_FPS_EVENT_H
#define VOYAGER_FPS_EVENT_H

#include "event.h"
#include "graphics/i_drawable.h"

namespace event_controller {
    class FPSEvent: public Event{
    public:
        FPSEvent(): Event(EventType::fps) {}
    };

}

#endif //VOYAGER_FPS_EVENT_H

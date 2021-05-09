//
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_I_CONTROLLER_H
#define VOYAGER_I_CONTROLLER_H

#include "event.h"
#include "i_subscriber.h"

namespace event_controller {
    class IController {
    public:
        virtual void subscribe(EventType type, ISubscriber &) = 0;

        virtual void unsubscribe(EventType type, ISubscriber &) = 0;
    };
}

#endif //VOYAGER_I_CONTROLLER_H

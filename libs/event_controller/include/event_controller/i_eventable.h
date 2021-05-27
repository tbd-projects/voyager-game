// Владимир Ларин
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_I_EVENTABLE_H
#define VOYAGER_I_EVENTABLE_H

#include <memory>

#include "event.h"

namespace event_controller {
    class IEventable {
    public:
        virtual std::unique_ptr<Event> get_event() = 0;

        virtual ~IEventable() = default;
    };
}

#endif //VOYAGER_I_EVENTABLE_H

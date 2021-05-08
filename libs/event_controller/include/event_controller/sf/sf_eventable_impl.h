//
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_SF_EVENTABLE_IMPL_H
#define VOYAGER_SF_EVENTABLE_IMPL_H

#include "event_controller/i_eventable.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace event_controller {
    class SfEventableImpl {
        virtual std::unique_ptr<Event> get_event(::sf::RenderWindow &window);
    };
}

#endif //VOYAGER_SF_EVENTABLE_IMPL_H

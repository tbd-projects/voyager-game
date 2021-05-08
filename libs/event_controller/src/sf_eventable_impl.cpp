//
// Created by volodya on 08.05.2021.
//

#include "event_controller/sf/sf_eventable_impl.h"
#include "graphics/sf/sf_canvas.h"

namespace event_controller {

    std::unique_ptr<Event> SfEventableImpl::get_event(sf::RenderWindow &window) {
        return std::unique_ptr<Event>();
    }
}
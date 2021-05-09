//
// Created by volodya on 08.05.2021.
//

#include "event_controller/controller.h"

namespace event_controller {
    void Controller::subscribe(EventType type, ISubscriber &subscriber) {

    }

    void Controller::unsubscribe(EventType type, ISubscriber &subscriber) {

    }

    void Controller::run() {

    }

    Controller::Controller(game_manager::GameManager &manager, IEventable &eventable) : _manager(manager), _eventable(eventable) {}
}
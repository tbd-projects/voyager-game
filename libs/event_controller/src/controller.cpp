//
// Created by volodya on 08.05.2021.
//

#include "event_controller/controller.h"

namespace event_controller {
    void Controller::subscribe(EventType type, ISubscriber &subscriber) {
        _subscribers[type].insert(&subscriber);
    }

    void Controller::unsubscribe(EventType type, ISubscriber &subscriber) {
        _subscribers[type].erase(&subscriber);
    }

   void Controller::run() {
        while (true) {
            std::unique_ptr<Event> event = _eventable.get_event();

            for (auto subscriber: _subscribers[event->type])
            {
                auto command = subscriber->update(*event);
                command->execute(_manager);
            }

            if (event->type == EventType::close) return;
        };
    }

    Controller::Controller(game_manager::GameManager &manager, IEventable &eventable)
    : _manager(manager), _eventable(eventable) {}
}
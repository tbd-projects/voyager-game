//
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_CONTROLLER_H
#define VOYAGER_CONTROLLER_H

#include <map>
#include <set>
#include "i_controller.h"
#include "i_eventable.h"

namespace event_controller {

class Controller : public IController {
  private:
    std::map<EventType, std::set<ISubscriber *>> _subscribers;
    game_manager::GameManager &_manager;
    IEventable &_eventable;
  public:
    Controller(game_manager::GameManager &manager, IEventable &eventable)
        : _manager(manager)
        , _eventable(eventable) {}

    void run() {}

    void stop() {}

    void subscribe(EventType type, ISubscriber &subscriber) override {}

    void unsubscribe(EventType type, ISubscriber &subscriber) override {}
};

}  // namespace event_controller

#endif  // VOYAGER_CONTROLLER_H

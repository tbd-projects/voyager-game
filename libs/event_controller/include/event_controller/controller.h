//
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_CONTROLLER_H
#define VOYAGER_CONTROLLER_H

#include <map>
#include <vector>
#include "i_controller.h"
#include "i_eventable.h"

namespace event_controller {

    class Controller : public IController{
    private:
        std::map<EventType, std::vector<ISubscriber *>> _subscribers;
        GameManager &_manager;
        IEventable &_eventable;
    public:
        Controller(GameManager &manager, IEventable &eventable);

        void run();
        void subscribe(EventType type, ISubscriber &subscriber) override;
        void unsubscribe(EventType type, ISubscriber &subscriber) override;
    };

}

#endif //VOYAGER_CONTROLLER_H

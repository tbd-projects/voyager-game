// Владимир Ларин
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_CONTROLLER_H
#define VOYAGER_CONTROLLER_H

#include <map>
#include <set>
#include "i_controller.h"
#include "i_eventable.h"

namespace event_controller {

    class Controller : public IController{
    private:
        bool _is_runned = false;
        std::map<EventType, std::set<ISubscriber *>> _subscribers;
        game_manager::GameManager &_manager;
        IEventable &_eventable;
        bool _need_update;

    public:
        Controller(game_manager::GameManager &manager, IEventable &eventable);

        void run();
        void stop();
        void subscribe(EventType type, ISubscriber &subscriber) override;
        void unsubscribe(EventType type, ISubscriber &subscriber) override;
    };

}

#endif //VOYAGER_CONTROLLER_H

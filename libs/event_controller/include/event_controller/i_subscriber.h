// Владимир Ларин
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_I_SUBSCRIBER_H
#define VOYAGER_I_SUBSCRIBER_H

#include <memory>
#include "i_command.h"
#include "event.h"

namespace event_controller {

    class ISubscriber {
    public:
        virtual std::shared_ptr<ICommand> update(Event &) = 0;
    };

}

#endif //VOYAGER_I_SUBSCRIBER_H

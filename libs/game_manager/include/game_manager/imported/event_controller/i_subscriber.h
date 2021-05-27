//
// Модуль Владимира Ларина
//

#ifndef VOYAGER_I_SUBSCRIBER_H
#define VOYAGER_I_SUBSCRIBER_H

#include <memory>
#include <game_manager/interface.hpp>
#include "event.h"

namespace event_controller {

class ISubscriber {
  public:
    virtual std::shared_ptr<game_manager::command::ICommand>
    update(Event &) = 0;
};

}

#endif  // VOYAGER_I_SUBSCRIBER_H

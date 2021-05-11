//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_I_MENU_H
#define VOYAGER_I_MENU_H


#include <event_controller/i_subscriber.h>
#include <event_controller/i_controller.h>

namespace menu {

class IMenu : public event_controller::ISubscriber {
  public:
    virtual event_controller::IController &get_controller() = 0;

    virtual ~IMenu() = default;
};

}  // namespace menu


#endif  // VOYAGER_I_MENU_H

//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_I_MENU_H
#define VOYAGER_I_MENU_H


#include <graphics/i_drawable.h>
#include <event_controller/i_subscriber.h>
#include <event_controller/i_controller.h>

namespace menu {
    class IMenu: public event_controller::ISubscriber {
    public:
        [[nodiscard]] virtual event_controller::IController &get_controller() const = 0;
        [[nodiscard]] virtual graphics::ICanvas &get_canvas() const = 0;
        virtual ~IMenu() = default;
    };
}


#endif //VOYAGER_I_MENU_H

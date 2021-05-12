//
// Created by volodya on 08.05.2021.
//

#include "game_manager/imported/menu/vertical_centered_menu.h"

namespace menu {

menu::VerticalCenteredMenu::VerticalCenteredMenu(graphics::ICanvas &canvas
                                 , event_controller::IController &controller)
        : _canvas(canvas)
          , _controller(controller) {}

event_controller::IController &menu::VerticalCenteredMenu::get_controller() {
    return _controller;
}

}  // namespace menu

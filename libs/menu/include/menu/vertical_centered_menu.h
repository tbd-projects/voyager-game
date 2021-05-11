//
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_VERTICAL_CENTERED_MENU_H
#define VOYAGER_VERTICAL_CENTERED_MENU_H


#include <event_controller/i_controller.h>
#include "graphics/i_drawable.h"
#include "i_menu.h"

#include <vector>

namespace menu {

class VerticalCenteredMenu : public IMenu {
  private:
    graphics::ICanvas &_canvas;
    event_controller::IController &_controller;

  public:
    VerticalCenteredMenu(graphics::ICanvas &canvas
                         , event_controller::IController &controller);

    event_controller::IController &get_controller() override;
};
}  // namespace menu

#endif  // VOYAGER_VERTICAL_CENTERED_MENU_H

//
// Модуль Владимира Ларина
//

#ifndef VOYAGER_VERTICAL_CENTERED_MENU_H
#define VOYAGER_VERTICAL_CENTERED_MENU_H

#include <game_manager/imported/event_controller/i_controller.h>
#include <game_manager/imported/graphics/i_drawable.h>

#include <vector>

#include "i_menu.h"

namespace menu {

class VerticalCenteredMenu : public IMenu {
  private:
    graphics::ICanvas &_canvas;
    event_controller::IController &_controller;

  public:
    VerticalCenteredMenu(graphics::ICanvas &canvas
                             , event_controller::IController &controller)
            : _canvas(canvas)
              , _controller(controller) {}

    event_controller::IController &get_controller() {
        return _controller;
    }
};
}  // namespace menu

#endif  // VOYAGER_VERTICAL_CENTERED_MENU_H

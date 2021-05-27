//
// Модуль Владимира Ларина
//

#ifndef VOYAGER_PAUSE_MENU_H
#define VOYAGER_PAUSE_MENU_H

#include "game_manager/imported/menu/i_menu.h"
#include <game_manager/imported/event_controller/event.h>
#include <game_manager/imported/graphics/i_drawable.h>
#include "game_manager/commands/nothing_command.hpp"

namespace menu {
class PauseMenu : public IMenu {
  public:
    ~PauseMenu() = default;

    std::shared_ptr<game_manager::command::ICommand>
    update(event_controller::Event &event) {
        return std::make_shared<game_manager::command::DoNothing>();
    }

    event_controller::IController &get_controller() {
        return *_controller;
    }

    PauseMenu(graphics::ICanvas &canvas
                         , event_controller::IController &controller) {}

  private:
    std::shared_ptr<event_controller::IController> _controller;
};

}  // namespace menu


#endif  // VOYAGER_PAUSE_MENU_H

//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_PAUSE_MENU_H
#define VOYAGER_PAUSE_MENU_H

#include "game_manager/imported/menu/i_menu.h"
#include <game_manager/imported/event_controller/event.h>
#include <game_manager/imported/graphics/i_drawable.h>

namespace menu {
class PauseMenu : public IMenu {
  public:
    ~PauseMenu() override;

    PauseMenu(graphics::ICanvas &canvas
              , event_controller::IController &controller);

    std::shared_ptr<game_manager::command::ICommand>
    update(event_controller::Event &event) override;

    event_controller::IController &get_controller() override;

  private:
    std::shared_ptr<event_controller::IController> _controller;
};

}  // namespace menu


#endif  // VOYAGER_PAUSE_MENU_H

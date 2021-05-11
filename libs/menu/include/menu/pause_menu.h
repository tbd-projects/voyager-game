//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_PAUSE_MENU_H
#define VOYAGER_PAUSE_MENU_H

#include "menu/i_menu.h"
#include <event_controller/event.h>

namespace menu {
class PauseMenu : public IMenu {
  public:
    ~PauseMenu() override;

    std::shared_ptr<game_manager::command::ICommand>
    update(event_controller::Event &event) override;

    event_controller::IController &get_controller() override;

  private:
    std::shared_ptr<event_controller::IController> _controller;
};

}  // namespace menu


#endif  // VOYAGER_PAUSE_MENU_H

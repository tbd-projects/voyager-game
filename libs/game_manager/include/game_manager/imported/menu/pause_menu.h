//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_PAUSE_MENU_H
#define VOYAGER_PAUSE_MENU_H

#include "imported/menu/i_menu.h"
#include <imported/event_controller/event.h>
#include <game_manager/commands.hpp>

namespace menu {
class PauseMenu : public IMenu {
  public:
    std::shared_ptr<game_manager::command::ICommand>
    update(event_controller::Event &event) override {
        return std::make_shared<game_manager::command::DoNothing>();
    }

    event_controller::IController &get_controller() override {
        return *_controller;
    }

  private:
    std::shared_ptr<event_controller::IController> _controller;
};

}  // namespace menu


#endif  // VOYAGER_PAUSE_MENU_H

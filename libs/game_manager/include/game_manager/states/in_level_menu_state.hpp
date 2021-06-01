#pragma once

#include <menu/levels_menu.h>
#include <event_controller/i_controller.h>
#include <graphics/i_drawable.h>
#include <game_manager/interface.hpp>

namespace game_manager::states {

class InLevelMenu : public IState {
  public:
    InLevelMenu() = delete;

    InLevelMenu(const InLevelMenu &) = delete;

    InLevelMenu &operator=(const InLevelMenu &) = delete;

    InLevelMenu(graphics::ICanvas &canvas,
                event_controller::IController &controller);

    void stop(event_controller::IController &controller) override;

    void resume(event_controller::IController &controller) override;

  private:
    menu::LevelsMenu _level_menu;
};

}  // namespace game_manager::states

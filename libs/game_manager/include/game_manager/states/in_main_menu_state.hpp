#pragma once

#include <menu/main_menu.h>
#include <event_controller/i_controller.h>
#include <graphics/i_drawable.h>
#include <game_manager/interface.hpp>

namespace game_manager::states {

class InMainMenu : public IState {
  public:
    InMainMenu() = delete;

    InMainMenu(const InMainMenu &) = delete;

    InMainMenu &operator=(const InMainMenu &) = delete;

    InMainMenu(graphics::ICanvas &canvas,
               event_controller::IController &controller);

    void stop(event_controller::IController &controller) override;

    void resume(event_controller::IController &controller) override;

  private:
    menu::MainMenu _main_menu;
};

}  // namespace game_manager::states

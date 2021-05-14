#pragma once

#include <game_manager/imported/menu/pause_menu.h>
#include <game_manager/imported/event_controller/i_controller.h>
#include <game_manager/imported/graphics/i_drawable.h>
#include <game_manager/interface.hpp>


namespace game_manager::states {

class InPauseMenu : public IState {
  public:
    InPauseMenu() = delete;

    InPauseMenu(const InPauseMenu&) = delete;
    InPauseMenu& operator=(const InPauseMenu&) = delete;

    InPauseMenu(graphics::ICanvas& canvas
                ,  event_controller::IController &controller);

    void stop(event_controller::IController &controller) override;

    void resume(event_controller::IController &controller) override;

  private:
    menu::PauseMenu _pause_menu;
};

}  // namespace game_manager::states

#pragma once

#include <event_controller/i_controller.h>
#include <graphics/i_drawable.h>
#include <menu/end_game_menu.h>
#include <game_manager/interface.hpp>
#include <game/structs.hpp>

namespace game_manager::states {

class GameOver : public IState {
  public:
    GameOver() = delete;

    GameOver(const GameOver&) = delete;
    GameOver& operator=(const GameOver&) = delete;

    GameOver(graphics::ICanvas& canvas
           ,  event_controller::IController &controller
           , bool status, const game::level_stat& stat);

    void stop(event_controller::IController &controller) override;

    void contine(event_controller::IController &controller) override;

  private:
    menu::EndGameMenu _game_over_menu;
};

}  // namespace game_manager::states

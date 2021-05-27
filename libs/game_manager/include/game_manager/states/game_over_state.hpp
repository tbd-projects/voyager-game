#pragma once

#include <game_manager/imported/event_controller/i_controller.h>
#include <game_manager/imported/graphics/i_drawable.h>
#include <game_manager/imported/menu/game_over.h>
#include <game_manager/interface.hpp>
#include <game_manager/imported/game/structs.hpp>

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
    menu::GameOverMenu _game_over_menu;
};

}  // namespace game_manager::states

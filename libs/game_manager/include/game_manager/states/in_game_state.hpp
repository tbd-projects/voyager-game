#pragma once

#include <game_manager/imported/event_controller/i_controller.h>
#include <game_manager/imported/graphics/i_drawable.h>
#include <game_manager/imported/game/game.hpp>
#include <game_manager/interface.hpp>

namespace game_manager::states {

class InGame : public IState {
  public:
    InGame() = delete;

    InGame(const InGame&) = delete;
    InGame& operator=(const InGame&) = delete;

    InGame(graphics::ICanvas& canvas
           ,  event_controller::IController &controller, size_t id_level);

    void stop(event_controller::IController &controller) override;

    void resume(event_controller::IController &controller) override;

  private:
    game::Game _game;
};

}  // namespace game_manager::states

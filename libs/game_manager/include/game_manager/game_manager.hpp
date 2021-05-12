#pragma once

#include <imported/menu/i_menu.h>
#include <imported/event_controller/controller.h>
#include <imported/event_controller/i_eventable.h>
#include <imported/graphics/i_drawable.h>
#include <imported/game/game.hpp>

namespace game_manager {

class GameManager {
  public:
    GameManager(graphics::ICanvas &canvas
                , event_controller::IEventable &eventable);

    void run();

    void start_game();

    void end_pause();

    void pause_game();

    void end_game();

    void exit();

    void open_main_menu();


  private:
    event_controller::Controller _controller;

    game::Game _game;
    graphics::ICanvas &_canvas;
    std::unique_ptr<menu::IMenu> _menu;

    bool _on_pause;
    bool _in_game;
};

}  // namespace game_manager

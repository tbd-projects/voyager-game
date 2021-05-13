#pragma once

#include <menu/i_menu.h>
#include <event_controller/controller.h>
#include <event_controller/i_eventable.h>
#include <graphics/i_drawable.h>
#include <game/game.hpp>

namespace game_manager {

class GameManager {
  public:
    GameManager(graphics::ICanvas &canvas
                , event_controller::IEventable &eventable);

    void run();

    void start_game(size_t id_level);

    void end_pause();

    void pause_game();

    void end_game();

    void exit();

    void open_main_menu();

    void open_levels_menu();


  private:
    event_controller::Controller _controller;

    std::unique_ptr<game::Game> _game;
    graphics::ICanvas &_canvas;
    std::unique_ptr<menu::IMenu> _menu;

    bool _on_pause;
    bool _in_game;
};

}  // namespace game_manager

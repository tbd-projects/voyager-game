//
// Модуль Ветошкина Артёма
//

#pragma once

#include <functional>

#include <event_controller/controller.h>
#include <event_controller/i_eventable.h>
#include <graphics/i_drawable.h>
#include <game_manager/interface.hpp>

namespace game_manager {

using func_create_state = std::function<
        std::unique_ptr<IState> (graphics::ICanvas &
                                   , event_controller::IController &)>;

class GameManager {
  public:
    GameManager(graphics::ICanvas &canvas
                , event_controller::IEventable &eventable);

    void run();

    void stash_state();

    void stash_state(const func_create_state& state);

    void apply_state();

    void add_state(const func_create_state& state);

    void end_run();

    void free_stash();

  private:
    event_controller::Controller _controller;
    graphics::ICanvas &_canvas;

    std::unique_ptr<IState> _current_state;
    std::unique_ptr<IState> _stash_state;
};

}  // namespace game_manager

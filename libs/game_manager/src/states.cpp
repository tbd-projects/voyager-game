#include "states.hpp"

namespace game_manager::states {


//  ------------------------------InMainMenu------------------------------------


InMainMenu::InMainMenu(graphics::ICanvas &canvas
                                 , event_controller::IController &controller)
        : _main_menu(canvas, controller) {}

void InMainMenu::stop(event_controller::IController &controller) const {
}

void InMainMenu::contine(event_controller::IController &controller) const {
}


//  ------------------------------InPauseMenu-----------------------------------


InPauseMenu::InPauseMenu(graphics::ICanvas &canvas
                                   , event_controller::IController &controller)
        : _pause_menu(canvas, controller) {}

void InPauseMenu::stop(event_controller::IController &controller) const {
}

void InPauseMenu::contine(
        event_controller::IController &controller) const {
}


//  --------------------------------InGame--------------------------------------


InGame::InGame(graphics::ICanvas &canvas
               , event_controller::IController &controller)
        : _game(controller, canvas) {}

void InGame::stop(event_controller::IController &controller) const {
    _game.stop_game(controller);
}

void InGame::contine(event_controller::IController &controller) const {
    _game.continue_game(controller);
}

}  // namespace game_manager::states

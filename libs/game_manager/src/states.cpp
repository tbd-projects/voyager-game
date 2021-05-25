#include "states.hpp"

namespace game_manager::states {


//  ------------------------------InMainMenu------------------------------------


InLevelMenu::InLevelMenu(graphics::ICanvas &canvas
        , event_controller::IController &controller)
        : _level_menu(canvas, controller) {}

void InLevelMenu::stop(event_controller::IController &controller)  {
}

void InLevelMenu::contine(event_controller::IController &controller)  {
}


//  ------------------------------InMainMenu------------------------------------


InMainMenu::InMainMenu(graphics::ICanvas &canvas
                                 , event_controller::IController &controller)
        : _main_menu(canvas, controller) {}

void InMainMenu::stop(event_controller::IController &controller)  {
}

void InMainMenu::contine(event_controller::IController &controller)  {
}


//  ------------------------------InPauseMenu-----------------------------------

InPauseMenu::InPauseMenu(graphics::ICanvas &canvas
                                   , event_controller::IController &controller)
        : _pause_menu(canvas, controller) {}

void InPauseMenu::stop(event_controller::IController &controller)  {
}

void InPauseMenu::contine(
        event_controller::IController &controller)  {
}


//  --------------------------------InGame--------------------------------------


InGame::InGame(graphics::ICanvas &canvas
               , event_controller::IController &controller
               , size_t id_level)
        : _game(controller, canvas) {
    _game.start_game(id_level);
}

void InGame::stop(event_controller::IController &controller)  {
    _game.stop_game();
}

void InGame::contine(event_controller::IController &controller)  {
    _game.unpause();
}

}  // namespace game_manager::states

#include "states.hpp"

namespace game_manager::states {

//  ------------------------------GameOver--------------------------------------


GameOver::GameOver(graphics::ICanvas &canvas
                         , event_controller::IController &controller
                   , bool status, const game::level_stat& stat)
        : _game_over_menu(canvas, controller) {
    _game_over_menu.set_data(status, stat);
}

void GameOver::stop(event_controller::IController &controller)  {
}

void GameOver::resume(event_controller::IController &controller)  {
}


//  ------------------------------InMainMenu------------------------------------


InLevelMenu::InLevelMenu(graphics::ICanvas &canvas
        , event_controller::IController &controller)
        : _level_menu(canvas, controller) {}

void InLevelMenu::stop(event_controller::IController &controller)  {
}

void InLevelMenu::resume(event_controller::IController &controller)  {
}


//  ------------------------------InMainMenu------------------------------------


InMainMenu::InMainMenu(graphics::ICanvas &canvas
                                 , event_controller::IController &controller)
        : _main_menu(canvas, controller) {}

void InMainMenu::stop(event_controller::IController &controller)  {
}

void InMainMenu::resume(event_controller::IController &controller)  {
}


//  ------------------------------InPauseMenu-----------------------------------

InPauseMenu::InPauseMenu(graphics::ICanvas &canvas
                                   , event_controller::IController &controller)
        : _pause_menu(canvas, controller) {}

void InPauseMenu::stop(event_controller::IController &controller)  {
}

void InPauseMenu::resume(
        event_controller::IController &controller)  {
}


//  --------------------------------InGame--------------------------------------


InGame::InGame(graphics::ICanvas &canvas
               , event_controller::IController &controller
               , size_t _id_level)
        : _game(controller, canvas) {
    _game.start_game(_id_level);
}

void InGame::stop(event_controller::IController &controller)  {
    _game.stop_game();
}

void InGame::resume(event_controller::IController &controller)  {
    _game.unpause();
}

}  // namespace game_manager::states

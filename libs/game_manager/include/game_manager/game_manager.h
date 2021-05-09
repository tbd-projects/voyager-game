//
// Created by volodya on 09.05.2021.
//

#ifndef VOYAGER_GAME_MANAGER_H
#define VOYAGER_GAME_MANAGER_H

#include <menu/i_menu.h>
#include <event_controller/i_controller.h>
#include <event_controller/i_eventable.h>
//#include <game/game.hpp>

namespace game_manager {
    class GameManager {
    private:
        std::unique_ptr<event_controller::IController> _controller;
//        Game _game;
        std::unique_ptr<::menu::IMenu> _menu;
        ::graphics::ICanvas& _canvas;
    public:
        GameManager(::graphics::ICanvas &canvas, event_controller::IEventable &eventable);

        void start_game();
        void pause_game();
        void end_game();
        void open_main_menu();
        void open_levels_menu();
    };
}


#endif //VOYAGER_GAME_MANAGER_H

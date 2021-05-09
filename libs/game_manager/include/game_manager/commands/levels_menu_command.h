//
// Created by volodya on 09.05.2021.
//

#ifndef VOYAGER_LEVELS_MENU_COMMAND_H
#define VOYAGER_LEVELS_MENU_COMMAND_H

#include <event_controller/i_command.h>
#include "game_manager.h"

namespace game_manager::command {

    class LevelsMenuCommand: public event_controller::ICommand {
        void execute(GameManager &manager) override {
            manager.open_levels_menu();
        }
    };
}


#endif //VOYAGER_LEVELS_MENU_COMMAND_H

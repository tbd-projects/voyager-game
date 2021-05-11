//
// Created by volodya on 09.05.2021.
//

#ifndef VOYAGER_START_GAME_COMMAND_H
#define VOYAGER_START_GAME_COMMAND_H

#include <event_controller/i_command.h>
#include "game_manager/game_manager.h"

namespace game_manager::command {

    class StartGameCommand: public event_controller::ICommand {
        void execute(GameManager &manager) override {
            manager.start_game();
        }

    };
}

#endif //VOYAGER_START_GAME_COMMAND_H

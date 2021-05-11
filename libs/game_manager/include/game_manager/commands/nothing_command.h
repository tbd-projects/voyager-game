//
// Created by volodya on 09.05.2021.
//

#ifndef VOYAGER_NOTHING_COMMAND_H
#define VOYAGER_NOTHING_COMMAND_H

#include <event_controller/i_command.h>

namespace game_manager::command {
    class NothingCommand: public event_controller::ICommand {
        void execute(GameManager &manager) override {

        }
    };
}

#endif //VOYAGER_NOTHING_COMMAND_H

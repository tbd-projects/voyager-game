//
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_I_COMMAND_H
#define VOYAGER_I_COMMAND_H

class GameManager; // @todo use external definition

namespace event_controller {

    class ICommand {
        virtual void execute(GameManager &manager) = 0;

        virtual ~ICommand() = default;
    };
}

#endif //VOYAGER_I_COMMAND_H

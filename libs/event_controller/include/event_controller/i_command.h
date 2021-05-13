//
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_I_COMMAND_H
#define VOYAGER_I_COMMAND_H

namespace game_manager {
    class GameManager;
}


namespace event_controller {
    class ICommand {
    public:
        virtual void execute(game_manager::GameManager &manager) = 0;

        virtual ~ICommand() = default;
    };
}

#endif //VOYAGER_I_COMMAND_H

//
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_COMMAND_BUTTON_H
#define VOYAGER_COMMAND_BUTTON_H

#include <graphics/button.h>

class ICommand {
public:
    virtual ~ICommand() = default;
}; // @todo use external defination

namespace menu {
    class CommandButton : public ::graphics::Button {
    private:
        std::unique_ptr<ICommand> _command;
    public:
        CommandButton(Button &&button, std::unique_ptr<ICommand> &&_command);

        [[nodiscard]] const std::unique_ptr<ICommand> &get_command() const;

        void set_command(std::unique_ptr<ICommand> &&command);
    };
}

#endif //VOYAGER_COMMAND_BUTTON_H

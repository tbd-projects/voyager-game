//
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_COMMAND_BUTTON_H
#define VOYAGER_COMMAND_BUTTON_H

#include <graphics/button.h>
#include <event_controller/i_command.h>

namespace menu {
    class CommandButton : public ::graphics::Button {
    private:
        std::unique_ptr<event_controller::ICommand> _command;
    public:
        CommandButton(Button &&button, std::unique_ptr<event_controller::ICommand> &&_command);

        [[nodiscard]] const std::unique_ptr<event_controller::ICommand> &get_command() const;

        void set_command(std::unique_ptr<event_controller::ICommand> &&command);
    };
}

#endif //VOYAGER_COMMAND_BUTTON_H

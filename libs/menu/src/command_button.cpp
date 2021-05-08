//
// Created by volodya on 08.05.2021.
//

#include "menu/command_button.h"

const std::unique_ptr<ICommand> &menu::CommandButton::get_command() const {
    return _command;
}

void menu::CommandButton::set_command(std::unique_ptr<ICommand> &&command) {
    _command = std::move(command);
}

menu::CommandButton::CommandButton(graphics::Button &&button,
                                   std::unique_ptr<ICommand> &&_command) : Button(std::move(button)) {

}

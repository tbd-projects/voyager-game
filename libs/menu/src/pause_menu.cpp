//
// Created by volodya on 15.04.2021.
//

#include "game_manager/commands.hpp"
#include "menu/pause_menu.h"

menu::PauseMenu::~PauseMenu() = default;

std::shared_ptr<event_controller::ICommand> menu::PauseMenu::update(event_controller::Event &event) {
    return std::make_shared<game_manager::command::NothingCommand>();
}

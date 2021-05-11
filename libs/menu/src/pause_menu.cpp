#include <game_manager/commands.hpp>
#include "menu/pause_menu.h"

namespace menu {

PauseMenu::~PauseMenu() = default;

std::shared_ptr<game_manager::command::ICommand>
PauseMenu::update(event_controller::Event &event) {
    return std::make_shared<game_manager::command::NothingCommand>();
}

event_controller::IController &PauseMenu::get_controller() {
    return *_controller;
}

}  // namespace menu

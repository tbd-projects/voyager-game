//
// Created by volodya on 15.04.2021.
//

#include <graphics/i_spite_loader.h>
#include "game_manager/imported/menu/main_menu.h"
#include <game_manager/commands.hpp>

namespace menu {

MainMenu::~MainMenu() = default;

MainMenu::MainMenu(graphics::ICanvas &canvas
                   , event_controller::IController &controller
                   , graphics::IGraphicsFactory &factory
                   , graphics::ISpiteLoader &loader)
        : VerticalCenteredMenu(canvas, controller) {
}

std::shared_ptr<game_manager::command::ICommand>
MainMenu::update(event_controller::Event &event) {
    return std::shared_ptr<game_manager::command::NothingCommand>();
}

}  // namespace menu

//
// Модуль Владимира Ларина
//

#ifndef VOYAGER_LEVELS_MENU_H
#define VOYAGER_LEVELS_MENU_H

#include "game_manager/imported/graphics/i_spite_loader.h"
#include "game_manager/imported/graphics/i_graphics_factory.h"
#include "game_manager/imported/menu/vertical_centered_menu.h"
#include "game_manager/commands/nothing_command.hpp"

namespace menu {

class LevelsMenu : public VerticalCenteredMenu {
  public:
    LevelsMenu(graphics::ICanvas &canvas
             , event_controller::IController &controller)
            : VerticalCenteredMenu(canvas, controller) {}

    std::shared_ptr<game_manager::command::ICommand>
    update(event_controller::Event &event) override {
        return std::make_shared<game_manager::command::DoNothing>();
    }

    ~LevelsMenu() override = default;
};

}  // namespace menu

#endif  // VOYAGER_LEVELS_MENU_H

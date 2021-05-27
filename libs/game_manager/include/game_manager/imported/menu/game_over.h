//
// Модуль Владимира Ларина
//

#ifndef VOYAGER_GAME_OVER_H
#define VOYAGER_GAME_OVER_H

#include "game_manager/imported/graphics/i_spite_loader.h"
#include "game_manager/imported/graphics/i_graphics_factory.h"
#include "game_manager/imported/menu/vertical_centered_menu.h"
#include "game_manager/imported/game/structs.hpp"
#include "game_manager/commands/nothing_command.hpp"

namespace menu {

class GameOverMenu : public VerticalCenteredMenu {
  public:
    GameOverMenu(graphics::ICanvas &canvas
               , event_controller::IController &controller, bool status
               , const game::level_stat& stat)
            : VerticalCenteredMenu(canvas, controller) {}

    std::shared_ptr<game_manager::command::ICommand>
    update(event_controller::Event &event) override {
        return std::make_shared<game_manager::command::DoNothing>();
    }

    ~GameOverMenu() override = default;
};
}  // namespace menu

#endif  // VOYAGER_GAME_OVER_H

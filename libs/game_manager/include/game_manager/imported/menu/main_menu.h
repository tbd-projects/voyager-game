//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_MAIN_MENU_H
#define VOYAGER_MAIN_MENU_H

#include "imported/graphics/i_spite_loader.h"
#include "imported/graphics/i_graphics_factory.h"
#include "imported/menu/vertical_centered_menu.h"
#include <game_manager/commands.hpp>

namespace menu {
class MainMenu : public VerticalCenteredMenu {
  public:
    MainMenu(graphics::ICanvas &canvas
             , event_controller::IController &controller
             , graphics::IGraphicsFactory &factory
             , graphics::ISpiteLoader &loader)
             : VerticalCenteredMenu(canvas, controller) {}

    std::shared_ptr<game_manager::command::ICommand>
    update(event_controller::Event &event) override {
        return std::shared_ptr<game_manager::command::DoNothing>();
    }

    ~MainMenu() override = default;
};

}  // namespace menu

#endif  // VOYAGER_MAIN_MENU_H

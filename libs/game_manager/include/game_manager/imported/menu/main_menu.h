//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_MAIN_MENU_H
#define VOYAGER_MAIN_MENU_H

#include "game_manager/imported/graphics/i_spite_loader.h"
#include "game_manager/imported/graphics/i_graphics_factory.h"
#include "game_manager/imported/menu/vertical_centered_menu.h"


namespace menu {
class MainMenu : public VerticalCenteredMenu {
  public:
    MainMenu(graphics::ICanvas &canvas
             , event_controller::IController &controller);

    std::shared_ptr<game_manager::command::ICommand>
    update(event_controller::Event &event) override;

    ~MainMenu() override;
};

}  // namespace menu

#endif  // VOYAGER_MAIN_MENU_H

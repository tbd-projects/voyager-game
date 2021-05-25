//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_PAUSE_MENU_H
#define VOYAGER_PAUSE_MENU_H

#include "menu/i_menu.h"
#include "menu/background_menu_decorator.h"
#include "menu/vertical_centered_menu.h"
#include "menu/i_create_menu_button.h"

namespace menu {
    class PauseMenu: public BackgroundMenuDecorator<VerticalCenteredMenu> {
    public:
        PauseMenu(graphics::ICanvas &canvas, event_controller::IController &controller, graphics::IGraphicsFactory &factory,
        graphics::ISpiteLoader &loader);

        PauseMenu(graphics::ICanvas &canvas, event_controller::IController &controller):
                PauseMenu(canvas,
                controller,
                *game_manager::Config::get_instance().graphics_factory,
        *game_manager::Config::get_instance().sprite_loader
        ) {};

        ~PauseMenu() override;
    private:
        graphics::IGraphicsFactory &_factory;
        graphics::ISpiteLoader &_loader;

        std::unique_ptr<ICreateMenuButton> _button_creator;
    };
}


#endif //VOYAGER_PAUSE_MENU_H

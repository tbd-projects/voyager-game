//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_MAIN_MENU_H
#define VOYAGER_MAIN_MENU_H

#include <game_manager/config.hpp>
#include "graphics/i_spite_loader.h"
#include "graphics/i_graphics_factory.h"
#include "graphics/texture_storage.h"
#include "menu/vertical_centered_menu.h"
#include "menu/background_menu_decorator.h"
#include "i_create_menu_button.h"


namespace menu {
    class MainMenu : public BackgroundMenuDecorator<VerticalCenteredMenu> {
    public:
        MainMenu(graphics::ICanvas &canvas, event_controller::IController &controller, graphics::IGraphicsFactory &factory,
                                         graphics::ISpiteLoader &loader);

        MainMenu(graphics::ICanvas &canvas, event_controller::IController &controller):
            MainMenu(canvas,
                     controller,
                     *game_manager::Config::get_instance().graphics_factory,
                     *game_manager::Config::get_instance().sprite_loader
                     ) {};

        ~MainMenu() override;

    private:
        graphics::IGraphicsFactory &_factory;
        graphics::ISpiteLoader &_loader;

        std::unique_ptr<ICreateMenuButton> _button_creator;
//        Progress _progress;

       };
}

#endif //VOYAGER_MAIN_MENU_H

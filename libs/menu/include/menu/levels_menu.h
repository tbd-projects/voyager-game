//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_LEVELS_MENU_H
#define VOYAGER_LEVELS_MENU_H

#include <game_manager/config.hpp>
#include "graphics/i_spite_loader.h"
#include "graphics/i_graphics_factory.h"
#include "graphics/texture_storage.h"
#include "menu/vertical_centered_menu.h"
#include "menu/background_menu_decorator.h"


namespace menu {
    class LevelsMenu : public BackgroundMenuDecorator<VerticalCenteredMenu> {
    public:
        LevelsMenu(graphics::ICanvas &canvas, event_controller::IController &controller, graphics::IGraphicsFactory &factory,
                 graphics::ISpiteLoader &loader, game::CreatorLevel &level_creator);

        LevelsMenu(graphics::ICanvas &canvas, event_controller::IController &controller):
                LevelsMenu(canvas,
                         controller,
                         *game_manager::Config::get_instance().graphics_factory,
                         *game_manager::Config::get_instance().sprite_loader,
                         *game_manager::Config::get_instance().levels_loader
                ) {};

        ~LevelsMenu() override;

    private:
        graphics::IGraphicsFactory &_factory;
        graphics::ISpiteLoader &_loader;
        game::CreatorLevel &_level_creator;
        std::unique_ptr<ICreateMenuButton> _button_creator;

    };
}

#endif //VOYAGER_LEVELS_MENU_H

//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_END_GAME_MENU_H
#define VOYAGER_END_GAME_MENU_H

#include <game_manager/config.hpp>
#include "graphics/i_spite_loader.h"
#include "graphics/i_graphics_factory.h"
#include "graphics/texture_storage.h"
#include "menu/vertical_centered_menu.h"
#include "menu/background_menu_decorator.h"
#include "i_create_menu_button.h"


namespace menu {
    class EndGameMenu : public BackgroundMenuDecorator<VerticalCenteredMenu> {
    public:
        EndGameMenu(graphics::ICanvas &canvas, event_controller::IController &controller, graphics::IGraphicsFactory &factory,
                                         graphics::ISpiteLoader &loader);

        EndGameMenu(graphics::ICanvas &canvas, event_controller::IController &controller):
            EndGameMenu(canvas,
                     controller,
                     *game_manager::Config::get_instance().graphics_factory,
                     *game_manager::Config::get_instance().sprite_loader
                     ) {};

        ~EndGameMenu() override;

        void set_data(bool status, const game::level_stat& stat);
        void set_active_id(int i) override;

    private:

        graphics::IGraphicsFactory &_factory;
        graphics::ISpiteLoader &_loader;

        std::unique_ptr<ICreateMenuButton> _button_creator;
       };
}

#endif //VOYAGER_END_GAME_MENU_H

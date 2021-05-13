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


namespace menu {
    class MainMenu : public VerticalCenteredMenu {
    public:
        MainMenu(graphics::ICanvas &canvas, event_controller::IController &controller, graphics::IGraphicsFactory &factory,
                                         graphics::ISpiteLoader &loader);

        MainMenu(graphics::ICanvas &canvas, event_controller::IController &controller):
            MainMenu(canvas,
                     controller,
                     *game_manager::Config::get_instance().graphics_factory,
                     *game_manager::Config::get_instance().sprite_loader
                     ) {};
        std::shared_ptr<event_controller::ICommand> update(event_controller::Event &event) override;


        ~MainMenu() override;

    private:
        graphics::IGraphicsFactory &_factory;
        graphics::ISpiteLoader &_loader;

        std::unique_ptr<graphics::Sprite> _bg;

        graphics::TextureStorage _storage;

//        Progress _progress;

        static menu::CommandButton
        _create_button(graphics::IGraphicsFactory &factory, std::shared_ptr<graphics::Font> &font,
                       std::unique_ptr<event_controller::ICommand> &&command, const std::string &title);
    };
}

#endif //VOYAGER_MAIN_MENU_H

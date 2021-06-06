//
// Created by volodya on 23.05.2021.
//

#ifndef VOYAGER_BACKGROUND_MENU_DECORATOR_H
#define VOYAGER_BACKGROUND_MENU_DECORATOR_H

#include <game_manager/config.hpp>
#include "i_menu.h"

namespace menu {
    template<class T>
    class BackgroundMenuDecorator : public T {
    private:
        graphics::IGraphicsFactory &_factory;
        graphics::ISpiteLoader &_loader;

        std::unique_ptr<graphics::Sprite> _bg;

        graphics::TextureStorage _storage;
    public:
        BackgroundMenuDecorator(graphics::ICanvas &canvas, event_controller::IController &controller, int bg_id,
                                graphics::IGraphicsFactory &factory,
                                graphics::ISpiteLoader &loader);

        BackgroundMenuDecorator(graphics::ICanvas &canvas, event_controller::IController &controller, int bg_id) :
                BackgroundMenuDecorator(canvas,
                                        controller,
                                        bg_id,
                                        *game_manager::Config::get_instance().graphics_factory,
                                        *game_manager::Config::get_instance().sprite_loader
                ) {};


        std::shared_ptr<event_controller::ICommand> update(event_controller::Event &event) override;

        ~BackgroundMenuDecorator() override = default;
    };
}

#include <menu/implimentation/background_menu_decorator.hpp>

#endif //VOYAGER_BACKGROUND_MENU_DECORATOR_H

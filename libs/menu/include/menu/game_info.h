//
// Created by volodya on 03.06.2021.
//

#ifndef VOYAGER_GAME_INFO_H
#define VOYAGER_GAME_INFO_H


#include "text_viewer.h"
#include "background_menu_decorator.h"

namespace menu {
    class GameInfo : public BackgroundMenuDecorator<TextViewer> {
    public:
        GameInfo(graphics::ICanvas &canvas, event_controller::IController &controller, graphics::IGraphicsFactory &factory,
                   graphics::ISpiteLoader &loader);

        GameInfo(graphics::ICanvas &canvas, event_controller::IController &controller):
                GameInfo(canvas,
                           controller,
                           *game_manager::Config::get_instance().graphics_factory,
                           *game_manager::Config::get_instance().sprite_loader
                ) {};

        std::shared_ptr<event_controller::ICommand> update(event_controller::Event &event) override;

        ~GameInfo() override;

    private:
        graphics::IGraphicsFactory &_factory;
        graphics::ISpiteLoader &_loader;
    };
}


#endif //VOYAGER_GAME_INFO_H

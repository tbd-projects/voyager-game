//
// Created by volodya on 24.05.2021.
//

#ifndef VOYAGER_GAME_SCREEN_H
#define VOYAGER_GAME_SCREEN_H

#include <graphics/i_drawable.h>
#include <graphics/i_graphics_factory.h>
#include <graphics/i_spite_loader.h>

namespace menu {
    class GameScreen: public graphics::IDrawable{
    public:
        GameScreen(graphics::IGraphicsFactory &factory, graphics::ISpiteLoader &loader,
                   graphics::TextureStorage &storage,
                   int screen_width = 0);

        void draw(graphics::ICanvas *canvas) override;

        void update(int timer, int fuel, int battery);

        void set_screen_width(int width);

    private:
        graphics::IGraphicsFactory &_factory;
        graphics::ISpiteLoader &_loader;
        graphics::TextureStorage &_storage;

        std::unique_ptr<graphics::Sprite> _fuel_icon;
        std::unique_ptr<graphics::Text> _fuel_text;

        std::unique_ptr<graphics::Sprite> _battery_icon;
        std::unique_ptr<graphics::Text> _battery_text;

        std::unique_ptr<graphics::Text> _timer_text;

        int _screen_width = 0;

        void _recount_positions();
    };
}

#endif //VOYAGER_GAME_SCREEN_H

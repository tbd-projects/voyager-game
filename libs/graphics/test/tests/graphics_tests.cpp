
#include <gtest/gtest.h>
#include "graphics/graphics.h"
#include "graphics/sf_graphics_factory.h"
#include "graphics/json_sprite_sheet_loader.h"
#include "graphics/sf_texture.h"
#include "graphics/sf_canvas.h"
#include "graphics/sf_text.h"
#include "graphics/sf_font.h"
#include <cmath>
#include <memory>

TEST (GraphicsTextureStorage, Get) {
    graphics::sf::SfGraphicsFactory loader;

    graphics::TextureStorage storage(loader);

    auto texture = storage.get("./libs/graphics/test/tests/sprites_info/1.png");

    ASSERT_EQ(texture->get_height(), 100);
    ASSERT_EQ(texture->get_width(), 100);
}


TEST (GraphicsTextureStorage, GetSprite) {
    graphics::sf::SfGraphicsFactory loader;

    graphics::TextureStorage storage(loader);

    graphics::sf::JsonSpriteSheetLoader sheet_loader(loader);

    auto sprite = sheet_loader.load(0, storage);
    auto canvas = loader.create_canvas();

    for (double i = 0; i <= 5000; ++i) {
        double x = i / 10.;
        double y = x * (1 + sin(x / 100));
        canvas->clear();
        sprite->draw(canvas);
        sprite->set_pos(std::pair(x, y));
        canvas->apply();
    }
}

TEST (GraphicsTextureStorage, SpriteAnimation) {
    graphics::sf::SfGraphicsFactory loader;

    graphics::TextureStorage storage(loader);

    graphics::sf::JsonSpriteSheetLoader sheet_loader(loader);

    auto sprite = dynamic_cast<graphics::AnimatedSprite *>(sheet_loader.load(1, storage).release());
    auto canvas = loader.create_canvas();

    for (int i = 0; i <= 5000; ++i) {
        double x = i / 100.;
        canvas->clear();
        sprite->draw(canvas);
        if (i % 50 == 0) sprite->next_frame();
        sprite->set_pos(std::pair(x, 100));
        canvas->apply();
    }
}


TEST (GraphicsTextureStorage, TextAnimation) {
    graphics::sf::SfGraphicsFactory loader;

    auto font = loader.create_font();
    font->set_path("./libs/graphics/test/tests/fonts/Roboto-Medium.ttf");
    font->set_color(std::tuple<char,char,char>(0,0,255));
    font->set_size(60);

    auto text = loader.create_text();
    text->set_font(font);
    text->set_string("Hello world!");

    auto canvas = loader.create_canvas();

    for (int i = 0; i <= 5000; ++i) {
        double x = i / 10.;
        double y = x * (1 + sin(x / 100));
        canvas->clear();
        text->set_pos(std::pair(x, y));
        text->draw(canvas);
        canvas->apply();
    }
}



#include <gtest/gtest.h>
#include "graphics.h"
#include "graphics/sf/sf_graphics_factory.h"
#include "graphics/json_sprite_sheet_loader.h"
#include "graphics/sf/sf_texture.h"
#include "graphics/sf/sf_canvas.h"
#include "graphics/sf/sf_text.h"
#include "graphics/sf/sf_font.h"
#include <cmath>
#include <memory>

auto cur_dir = std::filesystem::path(__FILE__).parent_path();

TEST (GraphicsTextureStorage, Get) {
    graphics::sf::SfGraphicsFactory loader;

    graphics::TextureStorage storage(loader);

    auto texture = storage.get(cur_dir / "./sprites_info/1.png");

    ASSERT_EQ(texture->get_height(), 100);
    ASSERT_EQ(texture->get_width(), 100);
}


TEST (GraphicsTextureStorage, GetSprite) {
    graphics::sf::SfGraphicsFactory loader;

    graphics::TextureStorage storage(loader);

    graphics::JsonSpriteSheetLoader sheet_loader(loader);

    auto sprite = sheet_loader.load(0, storage);
    auto canvas = loader.create_canvas();

    for (int i = 0; i <= 5000; ++i) {
        double x = i / 10.;
        double y = x * (1 + sin(x / 100));
        canvas->clear();
        sprite->draw(canvas);
        sprite->set_pos(math::coords_t(x, y));
        canvas->apply();
    }
}

TEST (GraphicsTextureStorage, SpriteAnimation) {
    graphics::sf::SfGraphicsFactory loader;

    graphics::TextureStorage storage(loader);

    graphics::JsonSpriteSheetLoader sheet_loader(loader);

    auto sprite = dynamic_cast<graphics::AnimatedSprite *>(sheet_loader.load(1, storage).release());
    auto canvas = loader.create_canvas();

    for (int i = 0; i <= 5000; ++i) {
        double x = i / 100.;
        canvas->clear();
        sprite->draw(canvas);
        if (i % 50 == 0) sprite->next_frame();
        sprite->set_pos(math::coords_t(x, 100));
        canvas->apply();
    }
}


TEST (GraphicsTextureStorage, SpriteAnimationRotation) {
    graphics::sf::SfGraphicsFactory loader;

    graphics::TextureStorage storage(loader);

    graphics::JsonSpriteSheetLoader sheet_loader(loader);

    auto sprite = dynamic_cast<graphics::AnimatedSprite *>(sheet_loader.load(1, storage).release());
    auto canvas = loader.create_canvas();

    sprite->set_pos(math::coords_t(100,100));
    for (int i = 0; i <= 5000; ++i) {
        canvas->clear();
        sprite->add_rotation(0.05);
        if (i % 50 == 0) sprite->next_frame();

        sprite->draw(canvas);
        canvas->apply();
    }
}


TEST (GraphicsTextureStorage, TextAnimation) {
    graphics::sf::SfGraphicsFactory loader;

    auto font = loader.create_font();
    font->set_path( cur_dir / "./fonts/Roboto-Medium.ttf");
    font->set_color(Color(0,0,255));
    font->set_size(60);

    auto text = loader.create_text();
    text->set_font(font);
    text->set_string("Hello world!");

    auto canvas = loader.create_canvas();

    for (int i = 0; i <= 5000; ++i) {
        double x = i / 10.;
        double y = 100 + x * (1 + sin(x / 100));
        canvas->clear();
        text->set_pos(math::coords_t(x, y));
        text->draw(canvas);
        canvas->apply();
    }
}


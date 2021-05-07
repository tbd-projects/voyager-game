
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


TEST (GraphicsTextureStorage, RectAnimation) {
    graphics::sf::SfGraphicsFactory loader;

    auto rect = loader.create_rect();

    rect->resize(120.2, 300);
    rect->set_border_color(Color(255, 0 , 0, 128));
    rect->set_border_width(2);
    rect->set_fill_color(Color(255,255,255));

    auto canvas = loader.create_canvas();

    for (int i = 0; i <= 5000; ++i) {
        double x = i / 10.;
        double y = 100 + x * (1 + sin(x / 100));
        canvas->clear();
        rect->set_pos(math::coords_t(x, y));
        rect->draw(canvas);
        canvas->apply();
    }
}


TEST (GraphicsTextureStorage, Button) {
    graphics::sf::SfGraphicsFactory loader;
    graphics::TextureStorage storage(loader);
    graphics::JsonSpriteSheetLoader spriteSheetLoader(loader);
    auto bg = spriteSheetLoader.load(2, storage);

    auto canvas = loader.create_canvas();

    auto center = math::coords_t(canvas->get_width() / 2.f, canvas->get_height() / 2.f);

    auto rect = loader.create_rect();
    rect->set_fill_color(Color(255,255,255));
    rect->set_border_color(Color(0,255,0));
    rect->set_border_width(10);
    rect->resize(canvas->get_height(), canvas->get_width());
    rect->set_pos(center);
    bg->set_pos(center);

    auto button = loader.create_button();

    auto font = loader.create_font();
    font->set_path( cur_dir / "./fonts/Roboto-Medium.ttf");
    button.set_font(font);

    std::string text("Hejjo world!");
    button.set_string("heh");
    button.set_padding(0);
    button.resize(100, 0);

    button.set_pos(center);


    for (int i = 0; i <= 5000; ++i) {
        canvas->clear();

        rect->draw(canvas);
        bg->draw(canvas);

        if ( i % 400 == 0)
        {
            auto t = text;
            t.resize(i / 450 + 1);
            button.set_string(t);
            button.set_focus(!button.is_focused());
        }

        button.draw(canvas.get());
        canvas->apply();
    }
}



TEST (GraphicsTextureStorage, Text) {
    graphics::sf::SfGraphicsFactory loader;

    auto font = loader.create_font();
    font->set_path( cur_dir / "./fonts/Roboto-Medium.ttf");
    font->set_color(Color(0,255,0));
    font->set_size(60);

    auto text = loader.create_text();
    text->set_font(font);
    text->set_string("O");
    text->set_pos(math::coords_t(0,0));

    auto canvas = loader.create_canvas();

    for (int i = 0; i <= 500; ++i) {
        canvas->clear();
        text->draw(canvas);
        canvas->apply();
    }
}


TEST (GraphicsTextureStorage, Button2) {
    graphics::sf::SfGraphicsFactory loader;
    auto canvas = loader.create_canvas();

    auto center = math::coords_t(canvas->get_width() / 2.f, canvas->get_height() / 2.f);

    auto button = loader.create_button();

    auto font = loader.create_font();
    font->set_path( cur_dir / "./fonts/Roboto-Medium.ttf");
    button.set_font(font);

    std::string text("Hejjo world!");
    button.set_string(text);
    button.set_padding(0);

    auto rext = loader.create_rect();
    rext->resize(10,10);
    rext->set_fill_color(Color(0,255,0));


    for (int i = 0; i <= 5000; ++i) {
        canvas->clear();

        double t = i / 500. * M_2_PI;
        double k = 100 * (1.2 + sin(t * 3));
        double x = center.x + 300 * cos(t);
        double y = center.y + 300 * sin(t);
        auto pos = math::coords_t(x,y);

        button.resize(k, 0);
        button.set_pos(pos);
        rext->set_pos(pos);

        button.draw(canvas.get());
        rext->draw(canvas.get());

        canvas->apply();
    }
}

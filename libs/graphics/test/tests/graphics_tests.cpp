// Владимир Ларин

#include <gtest/gtest.h>
#include "graphics.h"

#include "graphics/json_sprite_sheet_loader.h"

#include <sf_graphics/sf_graphics_factory.h>
#include <sf_graphics/sf_window.h>

#include <cmath>
#include <memory>


class MockJSONSpriteSheetLoader
        : public graphics::JsonSpriteSheetLoader
        {
public:
    explicit MockJSONSpriteSheetLoader(graphics::IGraphicsFactory &factory)
    : JsonSpriteSheetLoader(factory) {}
    std::filesystem::path _get_config_path() override
    {
        return std::filesystem::path(__FILE__).parent_path() / "sprites_info/some.json";
    }
};

class GraphicsTests : public ::testing::Test {
protected:
    std::filesystem::path _cur_dir = std::filesystem::path(__FILE__).parent_path();
    graphics::sf::SfGraphicsFactory _factory;
    ::sf::RenderWindow _sf_window;
    std::unique_ptr<graphics::ICanvas> _canvas;
    graphics::TextureStorage _storage;
    MockJSONSpriteSheetLoader _sprite_loader;
public:
    GraphicsTests(): _sf_window(
            ::sf::VideoMode::getDesktopMode(),
            "MyApp",
            sf::Style::Fullscreen
    ), _canvas(std::make_unique<::game_manager::SfWindow>(_sf_window)),
    _storage(_factory),
    _sprite_loader(_factory)
    {
    }

    std::shared_ptr<graphics::Font> get_font(){
        auto font = _factory.create_font();
        font->set_path( _cur_dir / "./fonts/Roboto-Medium.ttf");
        return font;
    }

    void SetUp() override {
        _canvas->clear();
    }

};


TEST_F (GraphicsTests, Get) {
    auto texture = _storage.get(_cur_dir / "./sprites_info/1.png");

    ASSERT_EQ(texture->get_height(), 100);
    ASSERT_EQ(texture->get_width(), 100);
}


TEST_F (GraphicsTests, GetSprite) {
    auto sprite = _sprite_loader.load(0, _storage);

    for (int i = 0; i <= 5000; ++i) {
        double x = i / 10.;
        double y = x * (1 + sin(x / 100));
        _canvas->clear();
        sprite->draw(_canvas);
        sprite->set_pos(math::coords_t(x, y));
        _canvas->apply();
    }
}

TEST_F (GraphicsTests, SpriteAnimation) {
    auto sprite = dynamic_cast<graphics::AnimatedSprite *>(_sprite_loader.load(1, _storage).release());
    for (int i = 0; i <= 5000; ++i) {
        double x = i / 100.;
        _canvas->clear();
        sprite->draw(_canvas);
        if (i % 50 == 0) sprite->next_frame();
        sprite->set_pos(math::coords_t(x, 100));
        _canvas->apply();
    }
}


TEST_F (GraphicsTests, SpriteAnimationRotation) {
    auto sprite = dynamic_cast<graphics::AnimatedSprite *>(_sprite_loader.load(1, _storage).release());
    sprite->set_pos(math::coords_t(100,100));

    for (int i = 0; i <= 5000; ++i) {
        _canvas->clear();
        sprite->add_rotation(0.05);
        if (i % 50 == 0) sprite->next_frame();

        sprite->draw(_canvas);
        _canvas->apply();
    }
}


TEST_F (GraphicsTests, TextAnimation) {
    auto font = get_font();
    auto text = _factory.create_text();
    text->set_font(font);

    text->set_color(Color(0,0,255));
    text->set_size(60);
    text->set_string("Hello world!");

    for (int i = 0; i <= 5000; ++i) {
        double x = i / 10.;
        double y = 100 + x * (1 + sin(x / 100));
        _canvas->clear();
        text->set_pos(math::coords_t(x, y));
        text->draw(_canvas);
        _canvas->apply();
    }
}


TEST_F (GraphicsTests, RectAnimation) {
    auto rect = _factory.create_rect();

    rect->resize(120.2, 300);
    rect->set_border_color(Color(255, 0 , 0, 128));
    rect->set_border_width(2);
    rect->set_fill_color(Color(255,255,255));


    for (int i = 0; i <= 5000; ++i) {
        double x = i / 10.;
        double y = 100 + x * (1 + sin(x / 100));
        _canvas->clear();
        rect->set_pos(math::coords_t(x, y));
        rect->draw(_canvas);
        _canvas->apply();
    }
}


TEST_F (GraphicsTests, Button) {
    auto bg = _sprite_loader.load(2, _storage);

    auto center = math::coords_t(_canvas->get_width() / 2.f, _canvas->get_height() / 2.f);

    auto rect = _factory.create_rect();
    rect->set_fill_color(Color(255,255,255));
    rect->set_border_color(Color(0,255,0));
    rect->set_border_width(10);
    rect->resize(_canvas->get_height(), _canvas->get_width());
    rect->set_pos(center);
    bg->set_pos(center);

    auto button = _factory.create_button();

    auto font = get_font();
    button.set_font(font);

    std::string text("Hejjo world!");
    button.set_string("heh");
    button.set_padding(0);
    button.resize(100, 0);

    button.set_pos(center);


    for (int i = 0; i <= 5000; ++i) {
        _canvas->clear();

        rect->draw(_canvas);
        bg->draw(_canvas);

        if ( i % 400 == 0)
        {
            auto t = text;
            t.resize(i / 450 + 1);
            button.set_string(t);
            button.set_focus(!button.is_focused());
        }

        button.draw(_canvas.get());
        _canvas->apply();
    }
}



TEST_F (GraphicsTests, Text) {
    auto font = get_font();

    auto text = _factory.create_text();
    text->set_font(font);
    text->set_color(Color(0,0,255));
    text->set_size(60);
    text->set_string("O");
    text->set_pos(math::coords_t(0,0));

    for (int i = 0; i <= 500; ++i) {
        _canvas->clear();
        text->draw(_canvas);
        _canvas->apply();
    }
}


TEST_F (GraphicsTests, Button2) {
    auto center = math::coords_t(_canvas->get_width() / 2.f, _canvas->get_height() / 2.f);

    auto button = _factory.create_button();

    auto font = get_font();
    button.set_font(font);

    std::string text("Hejjo world!");
    button.set_string(text);
    button.set_padding(0);

    auto rext = _factory.create_rect();
    rext->resize(10,10);
    rext->set_fill_color(Color(0,255,0));


    for (int i = 0; i <= 5000; ++i) {

        _canvas->clear();

        double t = i / 500. * M_2_PI;
        double k = 100 * (1.2 + sin(t * 3));
        double x = center.x + 300 * cos(t);
        double y = center.y + 300 * sin(t);
        auto pos = math::coords_t(x,y);

        button.resize(k, 0);
        button.set_pos(pos);
        rext->set_pos(pos);

        button.draw(_canvas.get());
        rext->draw(_canvas.get());

        _canvas->apply();
    }
}


TEST_F (GraphicsTests, Shape) {
    auto center = math::coords_t(_canvas->get_width() / 2.f, _canvas->get_height() / 2.f);

    auto shape = _factory.create_orbit();

    physics::Orbit::orbit_properties_t props;
    props.basis = center;
    props.variables = math::coords_t(100, 200);

    shape->set_orbit(props);
    shape->set_pos(math::coords_t(200, 200));

    for (int i = 0; i <= 5000; ++i) {
        _canvas->clear();
        props.angle_target += 0.01;
        props.variables.x += 0.25;
        props.variables.y -= 0.25;

        shape->set_orbit(props);

        shape->draw(_canvas);

        _canvas->apply();
    }
}

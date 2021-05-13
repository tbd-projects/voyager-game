#include <gtest/gtest.h>
#include "menu/vertical_centered_menu.h"
#include "menu/command_button.h"
#include "menu/main_menu.h"

#include <memory>
#include <sf_graphics/sf_graphics_factory.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <sf_graphics/sf_window.h>
#include <game_manager/commands.h>
#include <event_controller/event/fps_event.h>
#include <graphics/json_sprite_sheet_loader.h>
#include <event_controller/controller.h>
#include <event_controller/event/keyboard_event.h>

class MockController: public event_controller::IController {
public:
    void subscribe(event_controller::EventType type, event_controller::ISubscriber &subscriber) override {

    }

    void unsubscribe(event_controller::EventType type, event_controller::ISubscriber &subscriber) override {

    }
};


class MockJSONSpriteSheetLoader
        : public graphics::JsonSpriteSheetLoader
{
public:
    explicit MockJSONSpriteSheetLoader(graphics::IGraphicsFactory &factory)
            : JsonSpriteSheetLoader(factory) {}
    std::filesystem::path _get_config_path() override
    {
        return std::filesystem::path(__FILE__).parent_path() / "../../../../data/sprites.json";
    }
};

class MenuTests : public ::testing::Test {
protected:
    std::filesystem::path _cur_dir = std::filesystem::path(__FILE__).parent_path();
    graphics::sf::SfGraphicsFactory _factory;
    ::sf::RenderWindow _sf_window;
    std::unique_ptr<graphics::ICanvas> _canvas;
    graphics::TextureStorage _storage;
    MockJSONSpriteSheetLoader _sprite_loader;
    MockController _controller;
public:
    MenuTests(): _sf_window(
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
        font->set_path( _cur_dir / "../../../graphics/test/tests/fonts/Roboto-Medium.ttf");
        return font;
    }

    void SetUp() override {
        _canvas->clear();
    }

};



TEST_F(MenuTests, some)
{
    menu::VerticalCenteredMenu mmenu(*_canvas, _controller);
    auto font = get_font();

    for (int i = 0; i < 20; ++i) {
        auto btn1 = _factory.create_button();
        btn1.set_font(font);
        btn1.set_string(std::string("Button ") + std::to_string(i));
        btn1.set_padding(10);
        btn1.resize(50, 500);
        auto command1 = std::make_unique<game_manager::command::DoNothing>();
        auto cbtn1 = menu::CommandButton(std::move(btn1), std::move(command1));

        mmenu.buttons().push_back(std::move(cbtn1));
    }


    mmenu.set_buttons_height(50);
    mmenu.set_gap(10);


    for (int i = 0; i < 5000; ++i) {
        _canvas->clear();

        if( i % 200 == 0)
        {
            mmenu.set_active_id(i / 200 % mmenu.buttons().size());
        }
        event_controller::FPSEvent event;
        mmenu.update(event);


        _canvas->apply();
    }


}


TEST_F(MenuTests, some2)
{
    menu::MainMenu main_menu(*_canvas, _controller, _factory, _sprite_loader);

    for (int i = 0; i < 5000; ++i) {
        _canvas->clear();

        if( i % 200 == 0)
        {
            switch ((i / 200) % 3) {
                case 0: {
                    event_controller::KeyboardEvent event(event_controller::Key::Down);
                    main_menu.update(event);
                    break;
                }
                case 1: {
                    event_controller::KeyboardEvent event(event_controller::Key::Left);
                    main_menu.update(event);
                    break;
                }
                case 2: {
                    event_controller::KeyboardEvent event(event_controller::Key::Up);
                    main_menu.update(event);
                    break;
                }
            }
        }
        event_controller::FPSEvent event;
        main_menu.update(event);

        _canvas->apply();
    }


}

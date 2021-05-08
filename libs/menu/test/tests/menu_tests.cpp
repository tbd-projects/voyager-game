#include <gtest/gtest.h>
#include <menu/vertical_centered_menu.h>

#include <memory>
#include <menu/main_menu.h>
#include "graphics/sf/sf_graphics_factory.h"
#include "menu/command_button.h"

auto cur_dir = std::filesystem::path(__FILE__).parent_path();

TEST(some, some)
{
    graphics::sf::SfGraphicsFactory factory;

    auto canvas = factory.create_canvas(800, 600, false);

    auto font = factory.create_font();
    font->set_path(cur_dir / "../../../graphics/test/tests/fonts/Roboto-Medium.ttf");

    menu::VerticalCenteredMenu mmenu;


    for (int i = 0; i < 20; ++i) {
        auto btn1 = factory.create_button();
        btn1.set_font(font);
        btn1.set_string(std::string("Button ") + std::to_string(i));
        btn1.set_padding(10);
        btn1.resize(50, 500);
        auto command1 = std::make_unique<ICommand>();
        auto cbtn1 = menu::CommandButton(std::move(btn1), std::move(command1));

        mmenu.buttons().push_back(std::move(cbtn1));
    }


    mmenu.set_buttons_height(50);
    mmenu.set_gap(10);


    for (int i = 0; i < 5000; ++i) {
        canvas->clear();

        if( i % 200 == 0)
        {
            mmenu.set_active_id(i / 200 % mmenu.buttons().size());
        }
        FPSEvent event(*canvas);
        mmenu.update(event);


        canvas->apply();
    }


}


TEST(some, some2)
{
    graphics::sf::SfGraphicsFactory factory;

    auto canvas = factory.create_canvas(800, 600, false);

    menu::MainMenu mmenu(factory);

    for (int i = 0; i < 5000; ++i) {
        canvas->clear();

        if( i % 200 == 0)
        {
            mmenu.set_active_id(i / 200 % mmenu.buttons().size());
        }
        FPSEvent event(*canvas);
        mmenu.update(event);

        canvas->apply();
    }


}

//
// Created by volodya on 15.04.2021.
//

#include <create_standart_menu_button.h>
#include "game_manager/commands.hpp"
#include "menu/pause_menu.h"

menu::PauseMenu::~PauseMenu() = default;

menu::PauseMenu::PauseMenu(graphics::ICanvas &canvas, event_controller::IController &controller,
                           graphics::IGraphicsFactory &factory, graphics::ISpiteLoader &loader)
                           : BackgroundMenuDecorator(canvas, controller, 0, factory, loader),
_factory(factory),  _loader(loader) {
    _button_creator = std::make_unique<CreateStandartMenuButton>();

    set_gap(10);
    set_buttons_height(50);
    set_buttons_width(200);

    auto font = factory.create_font();

    auto cur_dir = std::filesystem::path(__FILE__).parent_path();
    font->set_path(cur_dir / "../../graphics/test/tests/fonts/Roboto-Medium.ttf");

    auto start_command = std::make_unique<game_manager::command::EndPause>();

    buttons().push_back(
            _button_creator->create(factory, font, std::move(start_command), "Continue")
    );
    auto other_command = std::make_unique<game_manager::command::RunMainMenu>();
    buttons().push_back(
            _button_creator->create(factory, font, std::move(other_command), "Go to menu")
    );


    set_active_id(0);
}



//
// Created by volodya on 23.05.2021.
//

#include <game_manager/commands.hpp>
#include <event_controller/event.h>
#include <create_standart_menu_button.h>
#include "levels_menu.h"

menu::LevelsMenu::LevelsMenu(graphics::ICanvas &canvas, event_controller::IController &controller,
                             graphics::IGraphicsFactory &factory, graphics::ISpiteLoader &loader,
                             game::CreatorLevel &level_creator) : BackgroundMenuDecorator(canvas, controller, 0),
                                                                  _factory(factory), _loader(loader),
                                                                  _level_creator(level_creator){
    _button_creator = std::make_unique<CreateStandartMenuButton>();

    set_gap(10);
    set_buttons_height(50);
    set_buttons_width(200);

    auto font = factory.create_font();

    auto cur_dir = std::filesystem::path(__FILE__).parent_path();
    font->set_path(cur_dir / "../../graphics/test/tests/fonts/Roboto-Medium.ttf");

    auto back_command = std::make_unique<game_manager::command::MainMenuCommand>();

    buttons().push_back(
            _button_creator->create(factory, font, std::move(back_command), "Back")
    );
    
    for (size_t i = 0; i < _level_creator.get_levels_count(); ++i) {
        size_t level = i + 1;
        auto command = std::make_unique<game_manager::command::StartGameCommand>(level);

        buttons().push_back(
                _button_creator->create(factory, font, std::move(command),
                               "Level " + std::to_string(level)
                )
        );
    }

    set_active_id(1);
}

menu::LevelsMenu::~LevelsMenu() = default;

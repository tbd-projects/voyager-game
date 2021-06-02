//
// Created by volodya on 15.04.2021.
//

#include <graphics/json_sprite_sheet_loader.h>
#include <create_standart_menu_button.h>
#include <loaders/locale_loader.h>
#include "menu/command_button.h"
#include "end_game_menu.h"
#include "game_manager/commands.hpp"
#include "event_controller/event/fps_event.h"

menu::EndGameMenu::~EndGameMenu() = default;

menu::EndGameMenu::EndGameMenu(graphics::ICanvas &canvas, event_controller::IController &controller, graphics::IGraphicsFactory &factory,
                         graphics::ISpiteLoader &loader) : BackgroundMenuDecorator(canvas, controller, 0, factory, loader),
                                                           _factory(factory),  _loader(loader) {
    _button_creator = std::make_unique<CreateStandartMenuButton>();
    LocaleLoader locale;

    set_gap(10);
    set_buttons_height(50);
    set_buttons_width(200);

    auto font = factory.create_font();

    auto cur_dir = std::filesystem::path(__FILE__).parent_path();
    font->set_path(cur_dir / "../../graphics/test/tests/fonts/Roboto-Medium.ttf");


    for (int i = 0; i < 4; ++i) {
        auto nothing_command = std::make_unique<game_manager::command::DoNothing>();
        buttons().push_back(
                _button_creator->create(factory, font, std::move(nothing_command), "")
        );

        buttons()[i].set_bg_color(Color(0,0,0,0));
        buttons()[i].set_text_color(Color(255,255,255));
    }

    auto restart_command = std::make_unique<game_manager::command::DoNothing>();
    buttons().push_back(
            _button_creator->create(factory, font, std::move(restart_command), locale.get("restart"))
    );

    auto main_menu_command = std::make_unique<game_manager::command::RunMainMenu>();
    buttons().push_back(
            _button_creator->create(factory, font, std::move(main_menu_command), locale.get("main_menu"))
    );

    auto exit_command = std::make_unique<game_manager::command::Exit>();
    buttons().push_back(
            _button_creator->create(factory, font, std::move(exit_command), locale.get("exit"))
    );

    set_active_id(1);
}

void menu::EndGameMenu::set_active_id(int i) {
    if (i < 4) i = 4;
    VerticalCenteredMenu::set_active_id(i);
}

void menu::EndGameMenu::set_data(bool status, const game::level_stat &stat) {
    LocaleLoader locale;
    buttons()[0].set_string(status ? locale.get("win") : locale.get("failure"));
    buttons()[1].set_string(locale.get("level") + ": " + std::to_string(stat.num));
    buttons()[2].set_string(locale.get("time") + ": " + std::to_string(stat.time_as_seconds));
    buttons()[3].set_string(locale.get("stars") + ": " + std::to_string(stat.stars));

    auto restart_command = std::make_unique<game_manager::command::RunGame>(stat.num);
    buttons()[4].set_command(std::move(restart_command));
}

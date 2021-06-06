//
// Created by volodya on 23.05.2021.
//

#include <game_manager/commands.hpp>
#include <event_controller/event.h>
#include <create_standart_menu_button.h>
#include <loaders/locale_loader.h>
#include "levels_menu.h"

menu::LevelsMenu::LevelsMenu(graphics::ICanvas &canvas, event_controller::IController &controller,
                             graphics::IGraphicsFactory &factory, graphics::ISpiteLoader &loader,
                             game::CreatorLevel &level_creator) : BackgroundMenuDecorator(canvas, controller, 0),
                                                                  _factory(factory), _loader(loader),
                                                                  _level_creator(level_creator){
    auto &config = game_manager::Config::get_instance();

    auto levels_stats = config.progress_loader->load(config.player_id).levels;

    LocaleLoader locale;
    _button_creator = std::make_unique<CreateStandartMenuButton>();

    set_gap(10);
    set_buttons_height(50);
    set_buttons_width(200);

    auto font = factory.create_font();

    auto cur_dir = std::filesystem::path(__FILE__).parent_path();
    font->set_path(cur_dir / "../../graphics/test/tests/fonts/Roboto-Medium.ttf");

    auto back_command = std::make_unique<game_manager::command::RunMainMenu>();

    buttons().push_back(
            _button_creator->create(factory, font, std::move(back_command), locale.get("back"))
    );

    size_t old_is_win = 0;
    for (size_t i = 0; i < _level_creator.get_levels_count(); ++i) {
        size_t level = i + 1;

        auto is_win_func = [level](const game::level_stat &stat) { return stat.num == level && stat.is_win;};
        auto is_win = std::find_if(levels_stats.begin(), levels_stats.end(), is_win_func) != levels_stats.end();

        std::unique_ptr<game_manager::command::ICommand> command;

        if (is_win || level - 1 == old_is_win)
        {
            command = std::make_unique<game_manager::command::RunGame>(level);
        }else {
            command = std::make_unique<game_manager::command::DoNothing>();
        }

        auto btn = _button_creator->create(factory, font, std::move(command),
                                           locale.get("level") + " " + std::to_string(level) +
                                           (is_win ? " " + locale.get("is_win"): "")
        );

        if (is_win)
        {
            btn.set_bg_color(Color(100,255,100));
            old_is_win = level;
        }
        else if(level - 1 == old_is_win)
        {
            btn.set_bg_color(Color(255,100,100));
        }else {
            btn.set_bg_color(Color(200,200,200));
        }

        buttons().push_back(std::move(btn));
    }

    set_active_id(old_is_win + 1);
}

menu::LevelsMenu::~LevelsMenu() = default;

//
// Created by volodya on 15.04.2021.
//

#include <graphics/json_sprite_sheet_loader.h>
#include "menu/command_button.h"
#include "menu/main_menu.h"
#include "game_manager/commands.hpp"
#include "event_controller/event/fps_event.h"

menu::MainMenu::~MainMenu() = default;

std::shared_ptr<event_controller::ICommand> menu::MainMenu::update(event_controller::Event &event) {
    if(event.type == event_controller::EventType::fps)
    {
        _bg->draw(&get_canvas());
    }

    if(event.type == event_controller::EventType::close)
    {
        return std::make_shared<game_manager::command::Exit>();
    }

    return VerticalCenteredMenu::update(event);
}


menu::MainMenu::MainMenu(graphics::ICanvas &canvas, event_controller::IController &controller, graphics::IGraphicsFactory &factory,
                         graphics::ISpiteLoader &loader) : VerticalCenteredMenu(canvas, controller),
                                                           _factory(factory),  _loader(loader), _storage(factory) {
    set_gap(10);
    set_buttons_height(50);
    set_buttons_width(200);

    auto font = factory.create_font();

    _bg = _loader.load(0, _storage);

    int dx = get_canvas().get_width() / 2;
    int dy = get_canvas().get_height() / 2;

    _bg->set_pos(math::coords_t(dx, dy));

    auto cur_dir = std::filesystem::path(__FILE__).parent_path();
    font->set_path(cur_dir / "../../graphics/test/tests/fonts/Roboto-Medium.ttf");

    auto start_command = std::make_unique<game_manager::command::StartGameCommand>(1); //@todo set level

    buttons().push_back(
            _create_button(factory, font, std::move(start_command), "Start game")
    );
    auto other_command = std::make_unique<game_manager::command::DoNothing>();
    buttons().push_back(
            _create_button(factory, font, std::move(other_command), "Game info")
    );

    auto exit_command = std::make_unique<game_manager::command::Exit>();
    buttons().push_back(
            _create_button(factory, font, std::move(exit_command), "Exit")
    );

    set_active_id(0);
}

menu::CommandButton
menu::MainMenu::_create_button(graphics::IGraphicsFactory &factory, std::shared_ptr<graphics::Font> &font,
                               std::unique_ptr<event_controller::ICommand> &&command, const std::string &title) {
    auto button = factory.create_button();
    button.set_font(font);
    button.set_string(title);

    button.set_bg_color(Color(255, 255, 255));
    button.set_text_color(Color(0, 0, 0));

    button.set_focus_bg_color(Color(0, 255, 255));
    button.set_text_color(Color(0, 0, 0));

    button.set_padding(10);

    return CommandButton(std::move(button), std::move(command));
}



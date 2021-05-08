//
// Created by volodya on 15.04.2021.
//

#include <graphics/json_sprite_sheet_loader.h>
#include "menu/command_button.h"
#include "menu/main_menu.h"

void menu::MainMenu::draw(graphics::ICanvas &canvas) {

}

menu::MainMenu::~MainMenu() = default;

void menu::MainMenu::update(Event &event) {
    if(event.type == event.fps)
    {
        _bg->draw(&dynamic_cast<FPSEvent &>(event).canvas);
    }

    VerticalCenteredMenu::update(event);
}

menu::MainMenu::MainMenu(graphics::IGraphicsFactory &factory)
        : _factory(factory), _storage(factory), _progress(nullptr) {
    set_gap(10);
    set_buttons_height(50);
    set_buttons_width(200);

    auto font = factory.create_font();

    graphics::JsonSpriteSheetLoader loader(factory);
    _bg = loader.load(0, _storage);

    int dx = _bg->get_texture_size().first / 2;
    int dy = _bg->get_texture_size().second / 2;

    _bg->set_pos(math::coords_t(dx, dy));

    auto cur_dir = std::filesystem::path(__FILE__).parent_path();
    font->set_path(cur_dir / "../../graphics/test/tests/fonts/Roboto-Medium.ttf");

    auto start_command = std::make_unique<ICommand>();

    buttons().push_back(
            _create_button(factory, font, std::move(start_command), "Start game")
    );

    buttons().push_back(
            _create_button(factory, font, std::move(start_command), "Game info")
    );

}

menu::CommandButton
menu::MainMenu::_create_button(graphics::IGraphicsFactory &factory, std::shared_ptr<graphics::Font> &font,
                               std::unique_ptr<ICommand> &&command, const std::string &title) {
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



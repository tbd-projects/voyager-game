//
// Created by volodya on 23.05.2021.
//

#include "menu/create_standart_menu_button.h"

menu::CommandButton menu::CreateStandartMenuButton::create(graphics::IGraphicsFactory &factory,
                                                           std::shared_ptr<graphics::Font> &font,
                                                           std::unique_ptr<event_controller::ICommand> &&command,
                                                           const std::string &title) {
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

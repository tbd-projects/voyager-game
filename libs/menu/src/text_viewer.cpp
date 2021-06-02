//
// Created by volodya on 03.06.2021.
//

#include <game_manager/commands/nothing_command.hpp>
#include <regex>
#include "../include/menu/text_viewer.h"

namespace menu{
TextViewer::TextViewer(graphics::ICanvas &canvas, event_controller::IController &controller,
                             graphics::IGraphicsFactory &factory):
                             VerticalCenteredMenu(canvas, controller) {

}

    void TextViewer::set_text(graphics::IGraphicsFactory &factory, const std::string &text) {
        set_gap(0);
        set_buttons_height(30);
        set_buttons_width(100);

        auto font = factory.create_font();

        auto cur_dir = std::filesystem::path(__FILE__).parent_path();
        font->set_path(cur_dir / "../../graphics/test/tests/fonts/Roboto-Medium.ttf");

        std::regex re("\n");
        std::sregex_token_iterator
                first{text.begin(), text.end(), re, -1},
                last;
        for (auto i = first; i != last; ++i) {
            buttons().push_back(_create_line(factory, font, *i));
        }

        set_active_id(0);
    }

    menu::CommandButton TextViewer::_create_line(graphics::IGraphicsFactory &factory,
                                                                  std::shared_ptr<graphics::Font> &font,
                                                                  const std::string &line) {
        auto button = factory.create_button();
        button.set_font(font);
        button.set_string(line);

        button.set_bg_color(Color(0,0,0, 0));
        button.set_text_color(Color(255,255,0));

        button.set_focus_bg_color(Color(0,0,0, 200));
        button.set_focus_text_color(Color(255, 255, 0));

        button.set_padding(5);

        return CommandButton(std::move(button), std::make_unique<game_manager::command::DoNothing>());
    }
}

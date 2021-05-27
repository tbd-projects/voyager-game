// Владимир Ларин
// Created by volodya on 06.05.2021.
//

#include "sf_window.h"
#include "sf_text.h"
#include "sf_font.h"

void graphics::sf::SfText::draw(graphics::ICanvas *canvas) {
    auto& window = dynamic_cast<game_manager::SfWindow *>(canvas)->get_sf_window();

    auto color = get_color();
    _sf_text.setFillColor(::sf::Color(color.red, color.green, color.blue));
    _sf_text.setCharacterSize(get_size());

    // sfml have some problems with text drawings, because use magic number here
    auto text_width = get_width();
    _sf_text.setOrigin(text_width / 2, get_size() * 0.724092001);


    auto position = get_pos();
    _sf_text.setPosition(position.x, position.y);

    window.draw(_sf_text);
}

void graphics::sf::SfText::set_font(std::shared_ptr<Font> font) {
    Text::set_font(font);

    auto &sf_font = dynamic_cast<graphics::sf::SfFont &>(get_font());
    _sf_text.setFont(sf_font.get_sf_font());

}

void graphics::sf::SfText::set_string(const std::string &string) {
    Text::set_string(string);

    _sf_text.setString(string);
}

int graphics::sf::SfText::get_width() {
    if (get_string().empty()) return 0;

    auto &sf_font = dynamic_cast<graphics::sf::SfFont &>(get_font());
    _sf_text.setFont(sf_font.get_sf_font());
    _sf_text.setCharacterSize(get_size());

    return _sf_text.getLocalBounds().width;

    return static_cast<int>(_sf_text.findCharacterPos(get_string().size() - 1).x
                            - _sf_text.findCharacterPos(0).x);
}

void graphics::sf::SfText::set_pos(math::coords_t pos) {
    PositionateObject::set_pos(pos);

    auto position = get_pos();
    _sf_text.setPosition(position.x, position.y);
}

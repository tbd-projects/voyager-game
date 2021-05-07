//
// Created by volodya on 06.05.2021.
//

#include "graphics/sf_text.h"
#include "graphics/sf_font.h"
#include "graphics/sf_canvas.h"


void graphics::sf::SfText::draw(graphics::ICanvas *canvas) {
    auto &sf_canvas = *dynamic_cast<SfCanvas *>(canvas);
    auto &window = sf_canvas.get_sf_window();

    window.draw(_sf_text);
}

void graphics::sf::SfText::set_font(std::shared_ptr<Font> font)
{
    Text::set_font(font);

    auto &sf_font = dynamic_cast<graphics::sf::SfFont &>(get_font());
    _sf_text.setFont(sf_font.get_sf_font());
    auto color = sf_font.get_color();
    _sf_text.setFillColor(
            ::sf::Color(
                    color.red,
                    color.green,
                    color.blue,
                    color.alpha
            )
    );

    _sf_text.setCharacterSize(sf_font.get_size());
}

void graphics::sf::SfText::set_string(const std::string &string) {
    Text::set_string(string);

    _sf_text.setString(string);
}

int graphics::sf::SfText::get_width() {
    return static_cast<int>(_sf_text.getLocalBounds().width);
}

void graphics::sf::SfText::set_pos(math::coords_t pos) {
    PositionateObject::set_pos(pos);

    auto position = get_pos();
    _sf_text.setPosition(position.x, position.y);
}

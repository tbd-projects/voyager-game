//
// Created by volodya on 07.05.2021.
//

#include "sf/sf_rect.h"
#include "sf/sf_canvas.h"

#include <SFML/Graphics/RectangleShape.hpp>

void graphics::sf::SfRect::draw(graphics::ICanvas *canvas) {
    auto& sf_canvas = *dynamic_cast<SfCanvas *> (canvas);

    ::sf::RectangleShape rect(::sf::Vector2f(get_width(), get_height()));

    auto fill_color = get_fill_color();
    rect.setFillColor(::sf::Color(fill_color.red, fill_color.green, fill_color.blue, fill_color.alpha));

    auto border_color = get_border_color();
    rect.setOutlineColor(::sf::Color(border_color.red, border_color.green, border_color.blue, border_color.alpha));

    auto width = static_cast<float>(get_border_width());
    rect.setOutlineThickness(width);


    auto pos = get_pos();
    rect.setPosition(pos.x, pos.y);

    rect.setOrigin(get_width() / 2, get_height() / 2);

    rect.setRotation(get_rotation());



    sf_canvas.get_sf_window().draw(rect);
}

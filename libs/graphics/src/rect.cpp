// Владимир Ларин
// Created by volodya on 07.05.2021.
//

#include "graphics/rect.h"

const Color &graphics::Rect::get_fill_color() const {
    return _fill_color;
}

void graphics::Rect::set_fill_color(const Color &fill_color) {
    _fill_color = fill_color;
}

const Color &graphics::Rect::get_border_color() const {
    return _border_color;
}

void graphics::Rect::set_border_color(const Color &border_color) {
    _border_color = border_color;
}

int graphics::Rect::get_border_width() const {
    return _border_width;
}

void graphics::Rect::set_border_width(int border_width) {
    _border_width = border_width;
}

//
// Created by volodya on 07.05.2021.
//

#include "button.h"

#include <utility>

const Color &graphics::Button::get_focus_text_color() const {
    return _focus_text_color;
}

void graphics::Button::set_focus_text_color(const Color &color) {
    _focus_text_color = color;
}

const Color &graphics::Button::get_focus_bg_color() const {
    return _focus_bg_color;
}

void graphics::Button::set_focus_bg_color(const Color &color) {
    _focus_bg_color = color;
}

const Color &graphics::Button::get_text_color() const {
    return _text_color;
}

void graphics::Button::set_text_color(const Color &color) {
    _text_color = color;
}

const Color &graphics::Button::get_bg_color() const {
    return _bg_color;
}

void graphics::Button::set_bg_color(const Color &color) {
    _bg_color = color;
}

bool graphics::Button::is_focused() const {
    return _is_focused;
}

void graphics::Button::set_focus(bool focused) {
    _is_focused = focused;
}

void graphics::Button::draw(graphics::ICanvas *canvas) {
    _update_drawables();

    _rect->draw(canvas);
    _text->draw(canvas);
}

void graphics::Button::set_pos(math::coords_t pos) {
    PositionateObject::set_pos(pos);
    _update_drawables();
}

void graphics::Button::_update_drawables() {
    if (is_focused()) {
        _rect->set_fill_color(_focus_bg_color);
        _text->set_color(_focus_text_color);
    } else {
        _rect->set_fill_color(_bg_color);
        _text->set_color(_text_color);
    }

    _text->set_size(std::max(static_cast<int>(get_height()) - get_padding() * 2, 0));

    auto width = std::max(get_width(), _text->get_width() + get_padding() * 2.f);
    if (width != get_width())
        resize(get_height(), width);

    _rect->resize(get_height(), width);

    _rect->set_pos(get_pos());
    _text->set_pos(get_pos());

    _rect->set_rotation(get_rotation());

}

void graphics::Button::set_rotation(math::decimal_t angle) {
    RotateObject::set_rotation(angle);
    _update_drawables();
}

void graphics::Button::resize(math::decimal_t height, math::decimal_t width) {
    RectanglePolygon::resize(height, width);
    _update_drawables();
}

void graphics::Button::scale(math::decimal_t scale) {
    RectanglePolygon::scale(scale);
    _update_drawables();
}

int graphics::Button::get_padding() const {
    return _padding;
}

void graphics::Button::set_padding(int padding) {
    _padding = padding;
    _update_drawables();
}

graphics::Button::Button(Rect *rect, Text *text) : _rect(rect), _text(text) {}

void graphics::Button::set_string(const std::string &string) {
    _text->set_string(string);
}

void graphics::Button::set_font(std::shared_ptr<Font> font) {
    _text->set_font(font);
}

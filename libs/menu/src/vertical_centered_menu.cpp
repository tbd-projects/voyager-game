//
// Created by volodya on 08.05.2021.
//

#include "menu/vertical_centered_menu.h"

void menu::VerticalCenteredMenu::update(Event &event) {
    if (event.type == event.fps)
    {
        auto &fps_event = dynamic_cast<FPSEvent &>(event);
        _draw(&fps_event.canvas);
    }
}

const menu::CommandButton& menu::VerticalCenteredMenu::get_active_button() const {
    return _buttons[_active_id];
}

void menu::VerticalCenteredMenu::set_active_id(int i) {
    _active_id = i;
}

int menu::VerticalCenteredMenu::get_buttons_height() const {
    return _buttons_height;
}

void menu::VerticalCenteredMenu::set_buttons_height(int height) {
    _buttons_height = height;
}

int menu::VerticalCenteredMenu::get_gap() const {
    return _gap;
}

void menu::VerticalCenteredMenu::set_gap(int gap) {
    _gap = gap;
}

void menu::VerticalCenteredMenu::_draw(graphics::ICanvas *canvas) {
    _update_buttons();

    for (auto &button: _buttons) {
        button.draw(canvas);
    }
}

void menu::VerticalCenteredMenu::_update_buttons() {
    int height = 600; // @todo get from settings
    int width = 800;

    math::coords_t center(width/ 2., height / 2.);

    int all_height = _buttons_height * _buttons.size()  + _gap * (_buttons.size() - 1);
    auto step = static_cast<math::decimal_t>(_buttons_height + _gap);

    math::decimal_t top = center.y - all_height / 2;
    if (all_height > height) {
        top -= (_active_id / static_cast<math::decimal_t>(_buttons.size()) - 0.5f) * all_height;

        if (top > _buttons_height) top = _buttons_height;
    }

    for (auto &button: _buttons) {
        button.resize(_buttons_height, _buttons_width);
        button.set_pos(math::coords_t(center.x, top));
        top += step;
        button.set_focus(false);
    }

    _buttons[_active_id].set_focus();

}

std::vector<menu::CommandButton> & menu::VerticalCenteredMenu::buttons() {
    return _buttons;
}

int menu::VerticalCenteredMenu::get_buttons_width() const {
    return _buttons_width;
}

void menu::VerticalCenteredMenu::set_buttons_width(int width) {
    _buttons_width = width;
}

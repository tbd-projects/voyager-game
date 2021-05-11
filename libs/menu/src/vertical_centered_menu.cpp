//
// Created by volodya on 08.05.2021.
//

#include <game_manager/commands.h>
#include "menu/vertical_centered_menu.h"
#include <event_controller/event/fps_event.h>
#include <event_controller/event/keyboard_event.h>

std::shared_ptr<event_controller::ICommand> menu::VerticalCenteredMenu::update(event_controller::Event &event) {
    if (event.type == event_controller::EventType::fps)
    {
        _draw(&_canvas);
    }
    if (event.type == event_controller::EventType::keyboard)
    {
        auto key = dynamic_cast<event_controller::KeyboardEvent &>(event).key;
        int size = buttons().size();
        switch (key) {
            case event_controller::Key::Up:
                set_active_id(std::min(_active_id + 1, size - 1));
                break;
            case event_controller::Key::Down:
                set_active_id(std::max(_active_id - 1, 0));
                break;
            default:
                break;
        }

    }
    return std::make_shared<game_manager::command::NothingCommand>();
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
    int height = _canvas.get_height();
    int width = _canvas.get_width();

    math::coords_t center(width/ 2., height / 2.);

    int full_height = _buttons_height * _buttons.size() + _gap * (_buttons.size() - 1);
    auto step = static_cast<math::decimal_t>(_buttons_height + _gap);

    math::decimal_t top = center.y - full_height / 2;
    if (full_height > height) {
        top -= (_active_id / static_cast<math::decimal_t>(_buttons.size()) - 0.5f) * full_height;

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

menu::VerticalCenteredMenu::VerticalCenteredMenu(graphics::ICanvas &canvas,
                                                 event_controller::IController &controller)
        : _canvas(canvas), _controller(controller) {}

graphics::ICanvas &menu::VerticalCenteredMenu::get_canvas() const {
    return _canvas;
}

event_controller::IController &menu::VerticalCenteredMenu::get_controller() {
    return _controller;
}

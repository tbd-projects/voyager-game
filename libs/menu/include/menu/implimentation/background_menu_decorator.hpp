//
// Created by volodya on 23.05.2021.
//

#include <graphics/i_graphics_factory.h>
#include <graphics/i_spite_loader.h>
#include "menu/background_menu_decorator.h"

template <typename T>
std::shared_ptr<event_controller::ICommand> menu::BackgroundMenuDecorator<T>::update(event_controller::Event &event) {
    if(event.type == event_controller::EventType::fps)
    {
        _bg->draw(T::get_canvas());
    }

    return T::update(event);
}

template <typename T>
menu::BackgroundMenuDecorator<T>::BackgroundMenuDecorator(graphics::ICanvas &canvas, event_controller::IController &controller, int bg_id, graphics::IGraphicsFactory &factory,
                                                       graphics::ISpiteLoader &loader): T(canvas, controller), _factory(factory),  _loader(loader), _storage(factory) {
    _bg = _loader.load(bg_id, _storage);

    int dx = T::get_canvas().get_width() / 2;
    int dy = T::get_canvas().get_height() / 2;

    _bg->set_pos(math::coords_t(dx, dy));

}

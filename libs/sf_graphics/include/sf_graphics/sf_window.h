//
// Created by volodya on 10.05.2021.
//

#ifndef VOYAGER_SF_WINDOW_H
#define VOYAGER_SF_WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>

#include <graphics/i_drawable.h>
#include <event_controller/i_eventable.h>

#include <sf_graphics/sf_canvas_impl.h>
#include <sf_graphics/sf_eventable_impl.h>

namespace game_manager {
    class SfWindow: public graphics::ICanvas, public event_controller::IEventable {
    private:
        ::sf::RenderWindow &_window;
    public:
        SfWindow(sf::RenderWindow &window) : _window(window) {}

        std::unique_ptr<event_controller::Event> get_event() override {
            return event_controller::SfEventableImpl::get_event(_window);
        }

        int get_width() override {
            return graphics::sf::SfCanvasImpl::get_width(_window);
        }

        int get_height() override {
            return graphics::sf::SfCanvasImpl::get_height(_window);
        }

        void clear() override {
            return graphics::sf::SfCanvasImpl::clear(_window);
        }

        void apply() override {
            return graphics::sf::SfCanvasImpl::apply(_window);
        }
        
        ::sf::RenderWindow& get_sf_window(){
            return _window;
        }
    };
}

#endif //VOYAGER_SF_WINDOW_H

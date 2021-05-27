// Владимир Ларин
// Created by volodya on 10.05.2021.
//

#include "sf_graphics/sf_canvas_impl.h"

namespace graphics::sf {
    int SfCanvasImpl::get_width(::sf::RenderWindow &window) {
        return static_cast<int>(window.getSize().x);
    }

    int SfCanvasImpl::get_height(::sf::RenderWindow &window) {
        return static_cast<int>(window.getSize().y);
    }

    void SfCanvasImpl::clear(::sf::RenderWindow &window) {
        window.clear();
    }

    void SfCanvasImpl::apply(::sf::RenderWindow &window) {
        window.display();
    }

}
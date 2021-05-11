//
// Created by volodya on 10.05.2021.
//

#ifndef VOYAGER_SF_CANVAS_IMPL_H
#define VOYAGER_SF_CANVAS_IMPL_H

#include <SFML/Graphics/RenderWindow.hpp>

namespace graphics::sf {

    class SfCanvasImpl {
    public:
        static int get_width(::sf::RenderWindow &window);

        static int get_height(::sf::RenderWindow &window);

        static void clear(::sf::RenderWindow &window);

        static void apply(::sf::RenderWindow &window);
    };

}
#endif //VOYAGER_SF_CANVAS_IMPL_H

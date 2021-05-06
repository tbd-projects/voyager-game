//
// Created by volodya on 02.05.2021.
//

#ifndef VOYAGER_SFCANVAS_H
#define VOYAGER_SFCANVAS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "i_drawable.h"

namespace graphics {


    class SfCanvas : public ICanvas {
    public:
        ::sf::RenderWindow window;

        SfCanvas();
        SfCanvas(int width, int height, bool is_full);

        ~SfCanvas() override;

        int get_width() override;

        int get_height() override;

        void clear() override;

        void apply() override;

        ::sf::RenderWindow& get_sf_window();
    };

}
#endif //VOYAGER_SFCANVAS_H

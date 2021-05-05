//
// Created by volodya on 02.05.2021.
//

#ifndef VOYAGER_SFCANVAS_H
#define VOYAGER_SFCANVAS_H

#include <SFML/Window.hpp>
#include "i_drawable.h"

namespace graphics {


    class SfCanvas : public ICanvas {
    public:
        ::sf::RenderWindow window;

        SfCanvas();

        virtual ~SfCanvas();

        int get_width() override;

        int get_height() override;

        void clear() override;

        void apply() override;
    };

}
#endif //VOYAGER_SFCANVAS_H

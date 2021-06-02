// Владимир Ларинs
// Created by volodya on 07.05.2021.
//

#ifndef VOYAGER_SF_RECT_H
#define VOYAGER_SF_RECT_H

#include <graphics/rect.h>

namespace graphics::sf {

    class SfRect: public Rect {
        void _draw(ICanvas *canvas) override;
    };
}


#endif //VOYAGER_SF_RECT_H

//
// Created by volodya on 06.05.2021.
//

#ifndef VOYAGER_POS_DRAWABLE_H
#define VOYAGER_POS_DRAWABLE_H

#include "graphics/i_drawable.h"
#include "graphics/i_texture.h"

namespace graphics {


    class PosDrawable: public IDrawable{

        std::pair<double, double> _pos = std::pair<double, double>(0, 0);
    public:
        virtual std::pair<double, double> get_pos();

        virtual void set_pos(const std::pair<double, double> &pos);
    };

}


#endif //VOYAGER_POS_DRAWABLE_H

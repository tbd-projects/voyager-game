//
// Created by volodya on 14.04.2021.
//

#ifndef VOYAGER_I_DRAWABLE_H
#define VOYAGER_I_DRAWABLE_H

namespace graphics {

    class ICanvas;

    class IDrawable {
    public:
        virtual void draw(ICanvas &) = 0;
        virtual ~IDrawable() = 0;
    };

}


#endif //VOYAGER_I_DRAWABLE_H

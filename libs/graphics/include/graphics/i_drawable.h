//
// Created by volodya on 14.04.2021.
//

#ifndef VOYAGER_I_DRAWABLE_H
#define VOYAGER_I_DRAWABLE_H

#include <utility>
#include <memory>

namespace graphics {

    class ICanvas {
    public:
        ICanvas() = default;

        virtual ~ICanvas() = default;

        virtual int get_width() = 0;

        virtual int get_height() = 0;

        virtual void clear() = 0;

        virtual void apply() = 0;
    };

    class IDrawable {
    public:
        virtual void draw(ICanvas *) = 0;
        virtual void draw(std::unique_ptr<ICanvas> &canvas) {
            draw(canvas.get());
        }

        virtual ~IDrawable() = default;
    };

}


#endif //VOYAGER_I_DRAWABLE_H

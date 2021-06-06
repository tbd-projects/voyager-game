// Владимир Ларин
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
    private:
        bool _is_visible = true;

        virtual void _draw(ICanvas *) = 0;
    public:
        void draw(std::unique_ptr<ICanvas> &canvas) {
            if (_is_visible) {
                _draw(canvas.get());
            }
        }
        void draw(ICanvas &canvas) {
            if (_is_visible) {
                _draw(&canvas);
            }
        }

        bool is_visible() const {
            return _is_visible;
        }

        virtual void set_visible(bool visible = true) {
            _is_visible = visible;
        }

        virtual ~IDrawable() = default;
    };

}


#endif //VOYAGER_I_DRAWABLE_H

//
// Created by volodya on 14.04.2021.
//

#ifndef VOYAGER_SPRITE_H
#define VOYAGER_SPRITE_H

#include "graphics/i_drawable.h"
#include "graphics/i_texture.h"
#include "math/polygon.hpp"

namespace graphics {
class Sprite : public IDrawable, public math::PositionateObject, public math::RotateObject, public math::IScalable  {
    private:
        math::decimal_t _scale = 1;
        std::pair<int, int> _texture_pos;
        std::pair<int, int> _texture_size;
        ITexture *_texture;
    public:
        Sprite(std::pair<int, int> pos, std::pair<int, int> size, ITexture *texture);

        virtual std::pair<int, int> get_texture_pos();

        virtual std::pair<int, int> get_texture_size();

        virtual ITexture &get_texture();

        ~Sprite() override = default;

        void scale(math::decimal_t scale) override;

        [[nodiscard]] math::decimal_t get_scale() const;
};

    class AnimatedSprite : public Sprite {

    public:
        AnimatedSprite(const std::pair<int, int> &pos, const std::pair<int, int> &size, ITexture *texture, int frames);

        AnimatedSprite(int frames, const Sprite &sprite);

        virtual int get_frames();

        virtual int get_current_frame();

        virtual void next_frame();

        ~AnimatedSprite() override = default;

    private:
        int _current_frame = 0;
        int _frames;
    };
}


#endif //VOYAGER_SPRITE_H

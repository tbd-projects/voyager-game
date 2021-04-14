//
// Created by volodya on 14.04.2021.
//

#ifndef VOYAGER_I_SPRITE_H
#define VOYAGER_I_SPRITE_H

#include "graphics/i_drawable.h"
#include "graphics/i_texture.h"

namespace graphics{
    class ISprite: public IDrawable {
    public:
        virtual std::pair<int,int> get_pos() = 0;
        virtual std::pair<int,int> get_size() = 0;
        virtual ITexture& get_texture() = 0;
        ~ISprite() override = 0;

    };

    class IAnimatedSprite: public ISprite {
    public:
        virtual int get_frames() = 0;
        virtual int get_current_frame() = 0;
        virtual void next_frame() = 0;
        ~IAnimatedSprite() override = 0;
    };
}


#endif //VOYAGER_I_SPRITE_H

//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_SF_SPRITE_H
#define VOYAGER_SF_SPRITE_H

#include <utility>
#include "graphics/i_sprite.h"
#include "graphics/sf_texture.h"

namespace graphics::sf {

    class SfSprite: public ISprite{
    public:
        SfSprite(std::pair<int, int> pos, std::pair<int, int> size, SfTexture &texture);
        std::pair<int, int> get_pos() override;
        std::pair<int, int> get_size() override;
        SfTexture &get_texture() override;

        void draw(ICanvas &canvas) override;

    private:
        SfTexture *_texture;
        std::pair<int,int> _size;
        std::pair<int,int> _pos;
    };

    class SfHorizontalAnimatedSprite: public IAnimatedSprite{
    public:
        SfHorizontalAnimatedSprite(int frames, SfSprite &&sprite);
        int get_frames() override;
        int get_current_frame() override;
        void next_frame() override;
        void draw(ICanvas &canvas) override;
        ~SfHorizontalAnimatedSprite() override;

    private:
        SfSprite _sprite;
        std::pair<int, int> get_pos() override;

        std::pair<int, int> get_size() override;

        SfTexture &get_texture() override;


    private:
        int _current_frame = 0;
        int _frames;
    };
}



#endif //VOYAGER_SF_SPRITE_H

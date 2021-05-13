//
// Created by volodya on 13.05.2021.
//

#ifndef VOYAGER_BACKGROUND_SPRITE_H
#define VOYAGER_BACKGROUND_SPRITE_H

#include "graphics/sprite.h"
namespace graphics {
    class BackgroundSprite: public Sprite {
        std::unique_ptr<Sprite> _sprite;
    public:
        explicit BackgroundSprite(std::unique_ptr<Sprite> &&sprite);

        std::pair<int, int> get_texture_pos() override;

        std::pair<int, int> get_texture_size() override;

        ITexture &get_texture() override;

        void draw(ICanvas *canvas) override;
    };
}

#endif //VOYAGER_BACKGROUND_SPRITE_H

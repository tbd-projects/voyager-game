// Владимир Ларин
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_SF_SPRITE_H
#define VOYAGER_SF_SPRITE_H

#include <utility>
#include "graphics/sprite.h"
#include "sf_texture.h"

namespace graphics::sf {

    class SfSprite : public Sprite {
    private:
        void _draw(ICanvas *canvas) override;
    public:
        SfSprite(
                const std::pair<int, int> &pos, const std::pair<int, int> &size, graphics::sf::SfTexture *texture
        );

    };

    class SfHorizontalAnimatedSprite : public AnimatedSprite {
    public:
        SfHorizontalAnimatedSprite(int frames, SfSprite &&sprite);

        SfHorizontalAnimatedSprite(int frames, const std::pair<int, int> &pos, const std::pair<int, int> &size,
                                   ITexture *texture);

        void _draw(ICanvas *canvas) override;

        ~SfHorizontalAnimatedSprite() override;
    };
}


#endif //VOYAGER_SF_SPRITE_H

//
// Created by volodya on 13.05.2021.
//

#include "background_sprite.h"
namespace graphics {
    std::pair<int, int> BackgroundSprite::get_texture_pos() {
        return _sprite->get_texture_pos();
    }

    std::pair<int, int> BackgroundSprite::get_texture_size() {
        return _sprite->get_texture_size();
    }

    ITexture &BackgroundSprite::get_texture() {
        return _sprite->get_texture();
    }

    void BackgroundSprite::draw(ICanvas *canvas) {
        auto w = canvas->get_width() , h = canvas->get_height();

        auto pos = get_pos();
        math::coords_t new_pos(0,0);
        auto scale = get_scale();
        _sprite->scale(scale);

        int ww = _sprite->get_texture_size().first * scale;
        int hh = _sprite->get_texture_size().second * scale;

        new_pos.x = (int(pos.x) % ww + ww) % ww - ww;
        new_pos.y = (int(pos.y) % hh + hh) % hh - hh;

        for (int x = new_pos.x; x < w + ww; x+=ww)
        {
            for (int y = new_pos.y; y < h + hh; y +=hh)
            {
                _sprite->set_pos(math::coords_t(x, y));
                _sprite->draw(canvas);
            }
        }
    }

    BackgroundSprite::BackgroundSprite(std::unique_ptr<Sprite> &&sprite):
        Sprite(
                sprite->get_texture_pos(),
                sprite->get_texture_size(),
                &sprite->get_texture()
                ),
        _sprite(std::move(sprite)) {

    }
}
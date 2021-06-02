// Владимир Ларин
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

    void BackgroundSprite::_draw(ICanvas *canvas) {
        auto w = canvas->get_width() , h = canvas->get_height();

        auto pos = get_pos();
        math::coords_t new_pos(0,0);
        auto scale = get_scale();
        _sprite->scale(scale);

        auto ww = _sprite->get_texture_size().first * scale;
        auto hh = _sprite->get_texture_size().second * scale;

        new_pos.x = ww * int(-pos.x/ww - 1) + pos.x;
        new_pos.y = hh * int(-pos.y/hh - 1) + pos.y;

        for (auto x = new_pos.x; x < w + ww; x += ww)
        {
            for (auto y = new_pos.y; y < h + hh; y += hh)
            {
                _sprite->set_pos(math::coords_t(x, y));
                _sprite->draw(*canvas);
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

    void BackgroundSprite::set_visible(bool visible) {}
}
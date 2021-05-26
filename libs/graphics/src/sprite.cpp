//
// Created by volodya on 05.05.2021.
//

#include "graphics/sprite.h"

#include <utility>

namespace graphics {

    std::pair<int, int> Sprite::get_texture_pos() {
        return _texture_pos;
    }

    std::pair<int, int> Sprite::get_texture_size() {
        return _texture_size;
    }

    ITexture &Sprite::get_texture() {
        return *_texture;
    }

    Sprite::Sprite(std::pair<int, int> pos, std::pair<int, int> size, ITexture *texture) :
            _texture_pos(std::move(pos)), _texture_size(std::move(size)), _texture(texture) {
        _size.x = _texture_size.first;
        _size.y = _texture_size.second;
    }

    void Sprite::scale(math::decimal_t scale) {
        _scale = scale;
    }

    math::decimal_t Sprite::get_scale() const {
        return _scale;
    }

    const math::coords_t &Sprite::get_size() const {
        return _size;
    }

    void Sprite::set_size(const math::coords_t &size) {
        _size = size;
    }


    int AnimatedSprite::get_frames() {
        return _frames;
    }

    int AnimatedSprite::get_current_frame() {
        return _current_frame;
    }

    void AnimatedSprite::next_frame() {
        ++_current_frame;
        _current_frame %= _frames;
    }

    AnimatedSprite::AnimatedSprite(const std::pair<int, int> &pos, const std::pair<int, int> &size, ITexture *texture,
                                   int frames) : Sprite(pos, size, texture), _frames(frames) {}

    AnimatedSprite::AnimatedSprite(int frames, const Sprite &sprite) : Sprite(sprite), _frames(frames) {}
}


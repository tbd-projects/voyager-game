//
// Created by volodya on 15.04.2021.
//

#include "sf_sprite.h"

std::pair<int, int> graphics::sf::SfSprite::get_pos() {
    return _pos;
}

std::pair<int, int> graphics::sf::SfSprite::get_size() {
    return _size;
}

graphics::sf::SfTexture &graphics::sf::SfSprite::get_texture() {
    return *_texture;
}

graphics::sf::SfSprite::SfSprite(std::pair<int, int> pos, std::pair<int, int> size,
                                 graphics::sf::SfTexture &texture): _texture(&texture) {

}

void graphics::sf::SfSprite::draw(graphics::ICanvas &canvas) {

}

graphics::sf::SfHorizontalAnimatedSprite::SfHorizontalAnimatedSprite(int frames, graphics::sf::SfSprite &&sprite)
: _sprite(sprite) , _frames(frames)  {
    if (!frames) throw;
}

int graphics::sf::SfHorizontalAnimatedSprite::get_frames() {
    return _frames;
}

int graphics::sf::SfHorizontalAnimatedSprite::get_current_frame() {
    return _current_frame;
}

void graphics::sf::SfHorizontalAnimatedSprite::next_frame() {
    ++_current_frame;
    _current_frame %= _frames;
}

void graphics::sf::SfHorizontalAnimatedSprite::draw(graphics::ICanvas &canvas) {
    _sprite.draw(canvas);
}

graphics::sf::SfHorizontalAnimatedSprite::~SfHorizontalAnimatedSprite() = default;

std::pair<int, int> graphics::sf::SfHorizontalAnimatedSprite::get_pos() {
    return _sprite.get_pos();
}

std::pair<int, int> graphics::sf::SfHorizontalAnimatedSprite::get_size() {
    return _sprite.get_size();
}

graphics::sf::SfTexture &graphics::sf::SfHorizontalAnimatedSprite::get_texture() {
    return _sprite.get_texture();
}

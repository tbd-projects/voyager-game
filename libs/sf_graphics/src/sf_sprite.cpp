//
// Created by volodya on 15.04.2021.
//

#include "sf_sprite.h"
#include "sf_window.h"

graphics::sf::SfSprite::SfSprite(
        const std::pair<int, int> &pos, const std::pair<int, int> &size, graphics::sf::SfTexture *texture
) : Sprite(pos, size, texture) {

}

void graphics::sf::SfSprite::draw(graphics::ICanvas *canvas) {
    auto& window = dynamic_cast<game_manager::SfWindow *>(canvas)->get_sf_window();

    ::sf::Sprite sprite;

    auto &texture = dynamic_cast<SfTexture &>(get_texture());
    auto crop_pos = get_texture_pos();
    auto crop_size = get_texture_size();

    sprite.setTexture(texture.get_sf_texture());

    sprite.setTextureRect(::sf::IntRect(
            crop_pos.first, crop_pos.second,
            crop_size.first, crop_size.second
    ));

    auto pos = get_pos();
    sprite.setPosition(pos.x, pos.y);

    auto dx = sprite.getGlobalBounds().width / 2;
    auto dy = sprite.getGlobalBounds().height / 2;

    sprite.setOrigin(dx, dy);

    auto angle = get_rotation();
    sprite.setRotation(-angle);

    window.draw(sprite);
}

graphics::sf::SfHorizontalAnimatedSprite::SfHorizontalAnimatedSprite(int frames, graphics::sf::SfSprite &&sprite)
        : AnimatedSprite(frames, sprite) {
    if (!frames) throw std::exception();
}

void graphics::sf::SfHorizontalAnimatedSprite::draw(graphics::ICanvas *canvas) {
    auto pos = get_texture_pos();
    auto size = get_texture_size();

    pos.first += get_current_frame() * size.first;
    SfSprite sprite(pos, size, &dynamic_cast<SfTexture &>(get_texture()));
    sprite.set_rotation(get_rotation());
    sprite.set_pos(get_pos());
    sprite.draw(canvas);
}

graphics::sf::SfHorizontalAnimatedSprite::SfHorizontalAnimatedSprite(
        int frames, const std::pair<int, int> &pos,
        const std::pair<int, int> &size,
        graphics::ITexture *texture) :
        AnimatedSprite(frames, SfSprite(pos, size, dynamic_cast<SfTexture *>(texture))) {

}

graphics::sf::SfHorizontalAnimatedSprite::~SfHorizontalAnimatedSprite() = default;

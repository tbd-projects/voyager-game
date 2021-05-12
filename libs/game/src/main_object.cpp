#include "main_object.hpp"

namespace game {
    const std::unique_ptr<graphics::Sprite> &GameObject::get_sprite() {
        return this->_sprite;
    }

    void GameObject::set_sprite(std::unique_ptr<graphics::Sprite> sprite) {
        this->_sprite = std::move(sprite);
    }

    void GameObject::set_sprite_id(size_t id) {
        this->_sprite_id = id;
    }

    void GameObject::rotate_sprite(math::decimal_t angle) {
//        this->_sprite->set_rotation(angle);
    }


    size_t GameObject::get_sprite_id() {
        return this->_sprite_id;
    }

    const std::unique_ptr<graphics::Sprite> &NotActiveObject::get_sprite() {
        return this->_sprite;
    }

    void NotActiveObject::set_sprite(std::unique_ptr<graphics::Sprite> sprite) {
        this->_sprite = std::move(sprite);
    }

    void NotActiveObject::set_sprite_id(size_t id) {
        this->_sprite_id = id;
    }

    size_t NotActiveObject::get_sprite_id() {
        return this->_sprite_id;
    }
} // namespace game

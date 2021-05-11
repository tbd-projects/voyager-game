#include "main_object.hpp"

namespace game {
    const std::unique_ptr<Sprite> &GameObject::get_sprite() {
        return this->_sprite;
    }

    void GameObject::set_sprite(std::unique_ptr<Sprite> sprite) {
        this->_sprite = std::move(sprite);
    }

    void GameObject::set_sprite_id(size_t id) {
        this->_sprite_id = id;
    }

    size_t GameObject::get_sprite_id() {
        return this->_sprite_id;
    }

    const std::unique_ptr<Sprite> &NotActiveObject::get_sprite() {
        return this->_sprite;
    }

    void NotActiveObject::set_sprite(std::unique_ptr<Sprite> sprite) {
        this->_sprite = std::move(sprite);
    }

    void NotActiveObject::set_sprite_id(size_t id) {
        this->_sprite_id = id;
    }

    size_t NotActiveObject::get_sprite_id() {
        return this->_sprite_id;
    }
} // namespace game

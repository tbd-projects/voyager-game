#include "main_object.hpp"

Sprite *GameObject::get_sprite() {
    return this->_sprite;
}

void GameObject::set_sprite(Sprite *sprite) {
    this->_sprite = sprite;
}

void GameObject::set_sprite_id(size_t id) {
    this->_sprite_id = id;
}
size_t GameObject::get_sprite_id() {
    return this->_sprite_id;
}

Sprite *NotActiveObject::get_sprite() {
    return this->_sprite;
}

void NotActiveObject::set_sprite(Sprite *sprite) {
    this->_sprite = sprite;
}

void NotActiveObject::set_sprite_id(size_t id) {
    this->_sprite_id = id;
}
size_t NotActiveObject::get_sprite_id() {
    return this->_sprite_id;
}

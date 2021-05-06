#include "main_object.hpp"

GameObject::GameObject(ISprite *sprite) {
    if (!sprite) {
        throw std::invalid_argument("Sprite ptr is invalid");
    }
}

GameObject::GameObject(size_t sprite_id) {

}

bool GameObject::check_collision(const Collision &collision) {
    return false;
}

GameObject::GameObject() {}


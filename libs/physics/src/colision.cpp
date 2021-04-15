#include "colision.hpp"

namespace physics {


//  -------------------------------Collision-----------------------------------


Collision::Collision(math::coords_t pos, math::decimal_t angle)
        : _pos(pos)
          , _angle(angle) {}

math::coords_t Collision::get_pos() const {
    return math::coords_t();
}

void Collision::set_pos(math::coords_t pos) {
}

void Collision::add_rotation(math::decimal_t offset_angle) {
}

void Collision::set_rotation(math::decimal_t angle) {
}

math::decimal_t Collision::get_rotation() const {
    return 0;
}


//  --------------------------RestangleCollision-------------------------------


RestangleCollision::RestangleCollision(math::coords_t pos
                                       , math::decimal_t height
                                       , math::decimal_t width
                                       , math::decimal_t angle)
        : Collision(pos, angle)
          , _height(height)
          , _width(width) {}

void RestangleCollision::resize(math::decimal_t height, math::decimal_t width) {
}

void RestangleCollision::scale(math::decimal_t scale) {
}

bool RestangleCollision::is_in_collision(math::coords_t point) const {
    return false;
}

bool RestangleCollision::check_collision
                                (const ICollisionable &collision) const {
    return false;
}


//  ---------------------------TriangleCollision-------------------------------


TriangleCollision::TriangleCollision(math::coords_t pos
                                   , math::decimal_t height
                                   , math::decimal_t width
                                   , math::decimal_t angle)
        : Collision(pos, angle)
          , _height(height)
          , _width(width) {}

void TriangleCollision::resize(math::decimal_t height, math::decimal_t width) {
}

void TriangleCollision::scale(math::decimal_t scale) {
}

bool TriangleCollision::is_in_collision(math::coords_t point) const {
    return false;
}

bool TriangleCollision::check_collision(const ICollisionable &collision) const {
    return false;
}


//  ---------------------------CircleCollision---------------------------------


CircleCollision::CircleCollision(math::coords_t pos
                                 , math::decimal_t radius
                                 , math::decimal_t angle)
        : Collision(pos, angle)
          , _radius(radius) {}

void CircleCollision::resize(math::decimal_t radius) {
}

void CircleCollision::scale(math::decimal_t scale) {
}

bool CircleCollision::is_in_collision(math::coords_t point) const {
    return false;
}

bool CircleCollision::check_collision(const ICollisionable &collision) const {
    return false;
}

}  // namespace physics

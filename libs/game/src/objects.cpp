#include "objects.hpp"


SpaceShip::SpaceShip(const SpaceShip &ship) : GameObject(ship._sprite) {
}


SpaceShip &SpaceShip::operator=(const SpaceShip &ship) {
    return *this;
}

bool SpaceShip::check_collision(const ICollisionable &collision) {
    return false;
}

Properties &SpaceShip::get_properties() {
    return this->_properties;
}

void SpaceShip::set_properties(Properties &properties) {

}

size_t SpaceShip::get_fuel() {
    return _properties.fuel;
}

size_t SpaceShip::get_health() {
    return _properties.health;
}

size_t SpaceShip::get_battery() {
    return _properties.battery;
}

size_t SpaceShip::get_engine() {
    return _properties.engine_power;
}

void SpaceShip::set_fuel() {
}

void SpaceShip::set_health() {
}

void SpaceShip::set_battery() {
}

void SpaceShip::set_engine() {
}

bool SpaceShip::create_object(IGameObject &object) {
    return false;
}

void SpaceShip::move(coords_t coords) {

}

bool SpaceShip::set_sprite() {
    return false;
}

ISprite &SpaceShip::get_sprite() {
    return *(this->_sprite);
}

void SpaceShip::set_sprite_id(size_t id) {

}

void SpaceShip::set_object_collision() {

}


SpaceBody::~SpaceBody() {
}

SpaceBody::SpaceBody(const SpaceBody &obj) : GameObject(obj._sprite) {

}

SpaceBody &SpaceBody::operator=(const SpaceBody &obj) {
    return *this;
}

bool SpaceBody::check_collision(const ICollisionable &collision) {
    return false;
}

Star::Star() {

}

Star &Star::operator=(const Star &obj) {
    return *this;
}

bool Star::check_collision(const ICollisionable &collision) {
    return false;

}

#include "objects.hpp"


properties_t &SpaceShip::get_properties() {
    return this->_properties;
}

void SpaceShip::set_properties(properties_t &properties) {

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

bool SpaceShip::set_sprite() {
    return false;
}

ISprite &SpaceShip::get_sprite() {
    return *(this->_sprite);
}

void SpaceShip::set_sprite_id(size_t id) {

}


SpaceBody::~SpaceBody() {
}


Star::Star() {

}

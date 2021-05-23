#include "objects.hpp"

namespace game {
    const properties_t &SpaceShip::get_properties() {
        return this->_properties;
    }

    void SpaceShip::set_properties(properties_t &properties) {
        this->_properties = properties;
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

    void SpaceShip::set_fuel(size_t fuel) {
        this->_properties.fuel = fuel;
    }

    void SpaceShip::set_health(size_t health) {
        this->_properties.health = health;
    }

    void SpaceShip::set_battery(size_t battery) {
        this->_properties.battery = battery;
    }

    void SpaceShip::set_engine(size_t engine) {
        this->_properties.engine_power = engine;
    }
    // @todo add fuel calculation formulas
    bool SpaceShip::update_fuel() {
        _properties.fuel /= 1;
        return this->_properties.fuel;
    }

    bool SpaceShip::update_battery() {
        return this->_properties.battery--;
    }

    bool SpaceShip::is_live() {
        return this->get_fuel() && this->get_battery() && this->get_health();
    }

    bool SpaceShip::is_die() {
        return !this->is_live();
    }
} // namespace game


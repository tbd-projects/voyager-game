// Дмитрий Варин
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

    math::decimal_t SpaceShip::get_fuel_density() {
        return this->_fuel_prop._fuel_density;
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

    void SpaceShip::set_fuel_density(math::decimal_t fuel_density) {
        this->_fuel_prop._fuel_density = fuel_density;
    }

    // @todo add _fuel_prop calculation formulas
    bool SpaceShip::update_fuel() {
        this->_properties.fuel -= this->_fuel_prop._base_discarder_mass_of_fuel / this->_fuel_prop._fuel_density;
        return this->_properties.fuel > 0;
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


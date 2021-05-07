#pragma once

#include "main_object.hpp"
#include "loaders/properties_loader.hpp"

class SpaceShip : public GameObject {
public:
    SpaceShip() = default;

    ~SpaceShip() = default;

    SpaceShip(const SpaceShip &ship) = delete;

    SpaceShip &operator=(const SpaceShip &ship) = delete;

    properties_t &get_properties();

    void set_properties(properties_t &properties);

    size_t get_fuel();

    size_t get_health();

    size_t get_battery();

    size_t get_engine();

    void set_fuel();

    void set_health();

    void set_battery();

    void set_engine();

    bool set_sprite() override;

    ISprite &get_sprite() override;

    void set_sprite_id(size_t id) override;

private:

    properties_t _properties;
};

class SpaceBody : public GameObject {
public:
    SpaceBody();

    SpaceBody(const SpaceBody &obj) = delete;

    SpaceBody &operator=(const SpaceBody &obj) = delete;

    ~SpaceBody();

};

class Star : public NotActiveObject {
public:
    Star();

    Star(const Star &) = delete;

    Star &operator=(const Star &obj) = delete;

    ~Star() = default;

};
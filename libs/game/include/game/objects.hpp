#pragma once

#include "main_object.hpp"
#include "loaders/properties_loader.hpp"

class SpaceShip : public GameObject {
public:
    SpaceShip();

    ~SpaceShip() = default;

    SpaceShip(const SpaceShip &ship);

    SpaceShip &operator=(const SpaceShip &ship);

    bool check_collision(const Collision &collision) override;

    Properties &get_properties();

    void set_properties(Properties &properties);

    size_t get_fuel();

    size_t get_health();

    size_t get_battery();

    size_t get_engine();

    size_t set_fuel();

    size_t set_health();

    size_t set_battery();

    size_t set_engine();

private:
    Properties _properties;
};

class SpaceBody : public GameObject {
public:
    SpaceBody();

    SpaceBody(const SpaceBody &obj);

    SpaceBody &operator=(const SpaceBody &obj);

    ~SpaceBody() = default;

    bool check_collision(const Collision &collision) override;

};

class Star : public NotActiveObject {
public:
    Star();

    Star &operator=(const Star &obj);

    ~Star() = default;


    bool check_collision(const Collision &collision) override;
};
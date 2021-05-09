#pragma once

#include "main_object.hpp"
#include "physics/astronomical_object.hpp"
#include "loaders/properties_loader.hpp"

class SpaceShip : public GameObject {
public:
    SpaceShip() = delete;

    ~SpaceShip() = default;

    SpaceShip(const SpaceShip &ship) = delete;

    SpaceShip &operator=(const SpaceShip &ship) = delete;

    properties_t &get_properties();

    void set_properties(properties_t &properties);

    size_t get_fuel();

    size_t get_health();

    size_t get_battery();

    size_t get_engine();

    void set_fuel(size_t fuel);

    void set_health(size_t health);

    void set_battery(size_t battery);

    void set_engine(size_t engine);

private:
    properties_t _properties;
};

class SpaceBody : public GameObject {
public:
    SpaceBody() = delete;

    SpaceBody(size_t sprite_id, std::unique_ptr<Sprite> &&sprite, std::unique_ptr<math::Polygon> &&pol,
              size_t weight, math::Vector2d velocity,
              math::coords_t pos, physics::Orbit::orbit_properties_t orbit) :
            GameObject(sprite_id, std::move(sprite), std::move(pol), weight, velocity, pos, orbit) {};

    SpaceBody(const SpaceBody &obj) = delete;

    SpaceBody &operator=(const SpaceBody &obj) = delete;

    ~SpaceBody() override = default;

};

class Star : public NotActiveObject {
public:
    Star() = delete;

    Star(size_t sprite_id, std::unique_ptr<Sprite> &&sprite, std::unique_ptr<math::Polygon> &&pol, math::coords_t pos,
         math::Vector2d velocity, size_t weight) :
            NotActiveObject(sprite_id, std::move(sprite), std::move(pol), pos, velocity, weight) {};

    Star(const Star &) = delete;

    Star &operator=(const Star &obj) = delete;

    ~Star() override = default;

};

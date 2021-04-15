#pragma once

#include "main_object.hpp"
#include "loaders/properties_loader.hpp"

class SpaceShip : public GameObject {
public:
    SpaceShip() = default;

    ~SpaceShip() = default;

    SpaceShip(const SpaceShip &ship);

    SpaceShip &operator=(const SpaceShip &ship);

    bool check_collision(const ICollisionable &collision);

    Properties &get_properties();

    void set_properties(Properties &properties);

    size_t get_fuel();

    size_t get_health();

    size_t get_battery();

    size_t get_engine();

    void set_fuel();

    void set_health();

    void set_battery();

    void set_engine();

    bool create_object(IGameObject &object);

    void move(coords_t coords) override;

    bool set_sprite() override;

    ISprite &get_sprite() override;

    void set_sprite_id(size_t id) override;

private:
    void set_object_collision() override;

    Properties _properties;
};

class SpaceBody : public GameObject {
public:
    SpaceBody();

    SpaceBody(const SpaceBody &obj);

    SpaceBody &operator=(const SpaceBody &obj);

    ~SpaceBody();

    bool check_collision(const ICollisionable &collision);

};

class Star : public NotActiveObject {
public:
    Star();

    Star &operator=(const Star &obj);

    ~Star() = default;


    bool check_collision(const ICollisionable &collision);
};
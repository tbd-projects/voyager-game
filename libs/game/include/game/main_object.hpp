#pragma once

#include "interface.hpp"
#include "physics/astronomical_object.hpp"


class GameObject : public IGameObject, public physics::AstronomicalObject {
public:
    explicit GameObject(ISprite *sprite);

    explicit GameObject(size_t sprite_id);

    GameObject();

protected:
    ISprite *_sprite;

private:
    size_t _sprite_id;
};


class NotActiveObject : public IGameObject, public physics::IMovable {
public:
    NotActiveObject();

protected:
    ISprite *_sprite;

private:
    size_t _sprite_id;
};

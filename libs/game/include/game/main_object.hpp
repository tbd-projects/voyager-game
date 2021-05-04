#pragma once

#include "interface.hpp"

class IMovable {

};

class ICollisionable {

};

class AstronomicalObject {

};

class GameObject : public IGameObject, public AstronomicalObject, public ICollisionable {
public:
    explicit GameObject(ISprite *sprite);

    explicit GameObject(size_t sprite_id);

    GameObject();

    //set sprite usage ISprite
    bool check_collision(const Collision &collision) override;
    // + redefine virtual funcs

protected:
    ISprite *_sprite{};

private:
    size_t _sprite_id{};
    Collision _base_collision;
};


class NotActiveObject : public IGameObject, public IMovable, public ICollisionable {
public:
    NotActiveObject();

private:
    ISprite *_sprite;
    size_t _sprite_id;
    Collision _base_collision;
};
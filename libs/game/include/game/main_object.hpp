#pragme once

#include "interface.hpp"

class IMovable;
class ICollisionable;
class AstronomicalObject;

class GameObject: public IGameObject, public AstronomicalObject, public ICollisionable {
public:
    GameObject(size_t sprite_id, );
    bool check_collision(const Collision &collision) override;

private:
    Sprite _sprite;
    size_t _sprite_id;
    Trigger _trigger;
    Collision _base_collision;
};


class NotActiveObject: public IGameObject, public physics::IMovable, public ICollisionable {
public:
    NotActiveObject();
private:
    Sprite _sprite;
    size_t _sprite_id;
    Trigger _trigger;
    Collision _base_collision;
};
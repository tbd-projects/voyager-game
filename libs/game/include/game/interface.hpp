#pragma once

#include <iostream>

using coords_t = std::pair<int, int>;

class ISprite {

};
class Collision {

};


class IGameObject {
public:
    IGameObject();

    virtual bool check_collision(const Collision &collision) = 0;

    virtual bool create_object(IGameObject &object) = 0;

    virtual void move(coords_t coords) = 0;

    virtual bool set_sprite() = 0;

    virtual ISprite &get_sprite() = 0;

    virtual void set_sprite_id(size_t id) = 0;

    virtual ~IGameObject() = 0;

private:
    virtual void set_object_collision() = 0;
};

